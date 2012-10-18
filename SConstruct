import os
import os.path as path
import platform

#------------------------set additional build options--------------------------
AddOption("--static",dest="static",action="store_true",
          default=False,help="create statically linked code")

#----------------add additional build variables--------------------------------
var = Variables()
var.Add("CXX","set the compiler to use","g++")
var.Add(PathVariable("PREFIX","Installation prefix","/usr"))
var.Add(PathVariable("BOOSTLIBDIR","BOOST library installation directory","/usr/lib"))
var.Add(PathVariable("BOOSTINCDIR","BOOST header installation directory","/usr/include"))


#---------------create the build environment-----------------------------------
env = Environment(variables=var,ENV={"PATH":os.environ["PATH"]})
#for the moment we relie on pkg-config for libpniutils
env["ENV"]["PKG_CONFIG_PATH"] = os.environ["PKG_CONFIG_PATH"]
env.ParseConfig('pkg-config --libs --cflags pninx')
env.Replace(CXX = env["CXX"])

#set some default compiler options
env.Append(CXXFLAGS=["-std=c++0x"])
env.Append(CXXFLAGS=["-Wall","-g","-O2","-fno-deduce-init-list"])

env.AppendUnique(CPPPATH=[env["BOOSTINCDIR"]])
env.AppendUnique(LIBPATH=[env["BOOSTLIBDIR"]])

Export("env")
(build_env,test_env) = SConscript("configure/SConscript")
program_env = build_env.Clone()

if GetOption("static"):
    program_env.Append(LIBS = ["pthread"])

gui_program_env = program_env.Clone()
gui_program_env.ParseConfig('pkg-config --libs --cflags QtGui')
gui_program_env.ParseConfig('pkg-config --libs --cflags QtCore')
Export("program_env")
Export("gui_program_env")


#start the SConscript files for the individual tools
SConscript("src/common/SConscript")
SConscript("src/detinfo/SConscript")
SConscript("src/mcaops/SConscript")
SConscript("src/xml2nx/SConscript")
SConscript("src/nxio/SConscript")
SConscript("src/nxbrowse/SConscript")
