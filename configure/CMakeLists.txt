include(CheckTypeSize)
include(CheckCXXSourceCompiles)
include(FindBoost)
include(FindPkgConfig)

if(NOT PKG_CONFIG_FOUND)
    message("Could not find pkg-config ... try without it!")
endif()
   
#setup for GNU CXX compiler
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
    message("found GNU compiler ...")
    if(CMAKE_BUILD_TYPE MATCHES RELEASE)
        message("setup for release build ...")
        add_definitions(-O3)
    elseif(CMAKE_BUILD_TYPE MATCHES DEBUG)
        message("setup for debug build ...")
        add_definitions(-O0 -g)
    endif()
endif()

#=====================check for BOOST libraries================================
find_package(Boost 1.49 COMPONENTS unit_test_framework)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Could not find BOOST libraries!")
endif()

#===================================check the size of data types===============
include(configure/CheckTypeSize.txt)

#we do not need to check for C++11 features as they are already checked during
#the build of the libraries. Required flags are imported via the pkg-config
#flags

#==========================check for libraries=====================================
#the only thing we have to do here is to check for pnicore
pkg_search_module(PNIIO_PKG REQUIRED pniio)

link_directories(${PNIIO_PKG_LIBRARY_DIRS})
include_directories(${PNIIO_PKG_INCLUDE_DIRS})
add_definitions(${PNIIO_PKG_CFLAGS})

