cmake_minimum_required(VERSION 2.6)
include(GNUInstallDirs)
project(pnitools)
set(CMAKE_VERBOSE_MAKEFILE ON)

#======================do here some setup work=================================
#setting the compiler flags
set(GCC_COMPILER_RELEASE_FLAGS "-std=c++11 -O3")
set(GCC_COMPILER_DEBUG_FLAGS "-std=c++11 -O0 -g")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILER_RELEASE_FLAGS}")

add_subdirectory("configure")
add_subdirectory("src/common")
add_subdirectory("src/det2nx")
add_subdirectory("src/detinfo")
add_subdirectory("src/mcaops")
add_subdirectory("src/nx2xml")
add_subdirectory("src/nxcat")
add_subdirectory("src/nxls")
add_subdirectory("src/nxsh")
#add_subdirectory("src/nxtee")
add_subdirectory("src/xml2nx")

