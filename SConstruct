import os
import os.path as path
import platform

#------------------------set additional build options--------------------------
AddOption("--static",dest="static",action="store_true",
          default=False,help="create statically linked code")

#----------------add additional build variables--------------------------------
var = Variables()
var.Add("CXX","set the compiler to use","g++")
var.Add(PathVariable("BOOSTLIBDIR","BOOST library installation directory","/usr/lib"))
var.Add(PathVariable("BOOSTINCDIR","BOOST header installation directory","/usr/include"))


#---------------create the build environment-----------------------------------
env = Environment(variables=var,ENV={"PATH":os.environ["PATH"]})
#for the moment we relie on pkg-config for libpniutils
env["ENV"]["PKG_CONFIG_PATH"] = os.environ["PKG_CONFIG_PATH"]
print env["ENV"]["PATH"]
env.ParseConfig('pkg-config --libs --cflags pniutils')
env.Replace(CXX = env["CXX"])

#set some default compiler options
env.Append(CXXFLAGS=["-std=c++0x"])
env.Append(CXXFLAGS=["-Wall","-g","-O2"])

env.AppendUnique(CPPPATH=[env["BOOSTINCDIR"]])
env.AppendUnique(LIBPATH=[env["BOOSTLIBDIR"]])

#------------------start with configuration------------------------------------
nullptr_test_code="""
int main(int argc,char **argv){
    char *ptr=nullptr;
    return 0;
}
"""

def CheckNullPtr(context):
    context.Message("Checking if compiler supports nullptr idiom ...")
    result = context.TryCompile(nullptr_test_code,".cpp")
    context.Result(result)
    return result

foreach_test_code="""
#include<iostream>
#include<vector>
int main(int argc,char **arv){
std::vector<int> vec = {1,2,3,4};
for(int &v: vec){
   std::cout<<v<<std::endl; 
}
return 0;
}
"""

def CheckForEach(context):
    context.Message("Check if compiler supports foreach loops ...")
    result = context.TryCompile(foreach_test_code,".cpp")
    context.Result(result)
    return result


conf = Configure(env,custom_tests = {"CheckNullPtr":CheckNullPtr,"CheckForEach":CheckForEach});

#checking compiler capabilities
if not conf.CheckNullPtr():
    print "nullptr not supported - use NULL"
    env.Append(CXXFLAGS=["-Dnullptr=NULL"])

if not conf.CheckForEach():
    print "foreach construction not supported - use workaround"
    env.Append(CXXFLAGS=["-DNOFOREACH"])
if not conf.CheckLib("boost_program_options"):
    print "BOOST program_options library not installed!"
    Exit(1)

env = conf.Finish()

if GetOption("static"):
    env.Append(LIBS = ["pthread"])



program_env = env.Clone()
Export("program_env")


#start the SConscript files for the individual tools
SConscript("src/mcaops/SConscript")
