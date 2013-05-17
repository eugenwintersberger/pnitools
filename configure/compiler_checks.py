#module contains custom check definitions for compiler features.


#======================check for nullptr=======================================
#This test checks whether or not the compiler supports the nullptr idiom of
#C++11

def CheckNullPtr(context):
    context.Message("Checking if compiler supports nullptr idiom ...")
    result = context.TryCompile(open('src/nullptr_test.cpp').read(),".cpp")
    context.Result(result)
    return result

#==================check for-each construction=================================
#Test checking for for(auto v: container) construction support

def CheckForEach(context):
    context.Message("Check if compiler supports foreach loops ...")
    result = context.TryCompile(open('src/foreach_test.cpp').read(),".cpp")
    context.Result(result)
    return result

#==============================explicit conversion check========================
#Check for explicit conversion operator support

def CheckForExplicitConversion(context):
    context.Message("Check if compiler supports explicit conversion operators ...")
    result = context.TryCompile(open('src/explicit_conversion_test.cpp').read(),".cpp")
    context.Result(result)
    return result

#========================check for C++11 random number facilities==============
#check for random number availability

def CheckForCppRandom(context):
    context.Message("Check for C++ pseudo random number facility ...")
    result = context.TryCompile(open('src/random_test.cpp').read(),".cpp")
    context.Result(result)
    return result

#=======================check for constexpr support============================
#test for constexpr support

def CheckForConstExpr(context):
    context.Message("Check for C++11 constexpr ...")
    result = context.TryCompile(open('src/constexpr_test.cpp').read(),".cpp")
    context.Result(result)
    return result

#=======================check for alias template support=======================
def CheckForTemplateAlias(context):
    context.Message("Check for C++11 alias templates ...")
    result = context.TryCompile(open('src/template_alias_test.cpp').read(),".cpp")
    context.Result(result)
    return result

#=======================check for enum class bug===============================
def CheckForEnumBug(context):
    context.Message("Check for enum bug ...")
    result = context.TryCompile(open('src/enum_bug_test.cpp').read(),".cpp")
    context.Result(result)
    return result

#dictionary holding the compiler checks
compiler_checks = {
                    "CheckNullPtr":CheckNullPtr,
                    "CheckForEach":CheckForEach,
                    "CheckExplicitConversion":CheckForExplicitConversion,
                    "CheckForCppRandom":CheckForCppRandom,
                    "CheckForConstExpr":CheckForConstExpr,
                    "CheckForTemplateAlias": CheckForTemplateAlias,
                    "CheckForEnumBug":CheckForEnumBug
                  }

def check_compiler_features(conf,env):
    """
    check_compiler_features(conf,env):
    Check compiler features and store flags in the environment env.

    required arguments:
    conf ........... configuration facility
    env ............ build environment

    return value:
    modivied env
    """

    #checking compiler capabilities
    if not conf.CheckNullPtr():
        print "nullptr not supported - use NULL"
        env.AppendUnique(CPPDEFINES=[('nullptr','NULL')])

    if not conf.CheckForEach():
        print "foreach construction not supported - use workaround"
        env.AppendUnique(CPPDEFINES=['NOFOREACH'])

    if not conf.CheckExplicitConversion():
        print "explicit conversion not supported by compiler!"
        env.AppendUnique(CPPDEFINES=['NOEXPLICITCONV'])

    if not conf.CheckForCppRandom():
        print "No C++11 random number generators!"
        env.AppendUnique(CPPDEFINES=['NOCPPRAND'])

    if not conf.CheckForConstExpr():
        print "Compiler does not support constexpr!"
        env.AppendUnique(CPPDEFINES=['NOCEXPR'])

    if not conf.CheckForTemplateAlias():
        print "Template aliases not supported!"
        env.AppendUnique(CPPDEFINES=['NOTMPALIAS'])

    if not conf.CheckForEnumBug():
        print "Compiler provides no comparsion operators for class enum types!"
        env.AppendUnique(CPPDEFINES=['ENUMBUG'])

    return env


def check_type_sizes(conf,env):
    """
    check_type_sizes(conf,env):
    Check the types for particular sizes. 

    positional arguments:
    conf ......... configuration facility
    env .......... build environment

    return:
    build environment
    """

    #check type sizes
    if not conf.CheckTypeSize('char',expect=1):
        pass

    if not conf.CheckTypeSize('unsigned char',expect=1):
        pass

    if not conf.CheckTypeSize('short',expect=2):
        pass

    if not conf.CheckTypeSize('unsigned short',expect=2):
        pass

    if not conf.CheckTypeSize('int',expect=4):
        pass

    if not conf.CheckTypeSize('unsigned int',expect=4):
        pass

    if not conf.CheckTypeSize('long',expect=8):
        pass

    if not conf.CheckTypeSize('unsigned long',expect=8):
        pass

    if not conf.CheckTypeSize('float',expect=4):
        pass

    if not conf.CheckTypeSize('double',expect=8):
        pass

    if not conf.CheckTypeSize('long double',expect = 16):
        #in this case we are on 32Bit PC platform
        pass

    return env

