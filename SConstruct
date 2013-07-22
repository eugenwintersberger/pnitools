import os
import os.path as path
import platform

#------------------------set additional build options--------------------------
AddOption("--static",dest="static",action="store_true",
          default=False,help="create statically linked code")
AddOption("--debug-build",dest="debug",action="store_true",
          default=False,help="build debuging release")

#----------------add additional build variables--------------------------------
var = Variables()
var.Add("CXX","set the compiler to use","g++")
var.Add(PathVariable("PREFIX","Installation prefix","/usr"))
var.Add(PathVariable("BOOSTLIBDIR","BOOST library installation directory","/usr/lib"))
var.Add(PathVariable("BOOSTINCDIR","BOOST header installation directory","/usr/include"))
var.Add(PathVariable("QT4DIR","QT4 installation directory","/usr"))


#---------------create the build environment-----------------------------------
env = Environment(variables=var,ENV={"PATH":"/usr/lib/ccache:"+os.environ["PATH"]},tools=['default'])
#check if the user has set PKG_CONFIG_PATH to some additional location
try:
    env["ENV"]["PKG_CONFIG_PATH"] = os.environ["PKG_CONFIG_PATH"]
except:
    pass

#------------------------set library paths-------------------------------------
#set boost installation directories
env.AppendUnique(CPPPATH=[env["BOOSTINCDIR"]])
env.AppendUnique(LIBPATH=[env["BOOSTLIBDIR"]])


#----------------------set the compiler and compiler options-------------------
#set the compiler
env.Replace(CXX = env["CXX"])
#set some default compiler options
env.Append(CXXFLAGS=["-std=c++0x"])
env.Append(CXXFLAGS=["-Wall","-fno-deduce-init-list","-Wno-deprecated"])

if GetOption("debug"):
    env.Append(CXXFLAGS=["-g","-O0"])
else:
    env.Append(CXXFLAGS=["-O2"])

env.ParseConfig('pkg-config --libs --cflags pniio')


#--------------------start here with configuration-----------------------------
Export("env")
(cli_env,gui_env,test_env) = SConscript("configure/SConscript")

Export("cli_env")
Export("gui_env")
Export("test_env")


#start the SConscript files for the individual tools
SConscript("src/common/SConscript")
SConscript("src/detinfo/SConscript")
SConscript("src/mcaops/SConscript")
SConscript("src/xml2nx/SConscript")
SConscript("src/nxcat/SConscript")
SConscript("src/nxsh/SConscript")
SConscript("doc/man/SConscript")
SConscript("src/det2nx/SConscript")
#SConscript("src/nxtee/SConscript")
#SConscript("src/nxbrowse/SConscript")
SConscript("src/detview/SConscript")
SConscript("src/nxls/SConscript")
SConscript("src/nx2xml/SConscript")
SConscript("test/SConscript")
