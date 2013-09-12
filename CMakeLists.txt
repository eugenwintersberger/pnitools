cmake_minimum_required(VERSION 2.6)
project(pnitools)

set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_BINDIR "${CMAKE_INSTALL_PREFIX}/bin")
set(CMAKE_INSTALL_SYSCONFDIR "${CMAKE_INSTALL_PREFIX}/etc")
set(CMAKE_INSTALL_SHAREDIR "${CMAKE_INSTALL_PREFIX}/share")
set(CMAKE_INSTALL_DOCDIR "${CMAKE_INSTALL_PREFIX}/share/doc")
set(CMAKE_INSTALL_INFODIR "${CMAKE_INSTALL_PREFIX}/share/info")
set(CMAKE_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_PREFIX}/include")


if(NOT CMAKE_BUILD_TYPE)
    message("No build type specified - default is RELEASE")
    set(CMAKE_BUILD_TYPE RELEASE)
endif()
#======================do here some setup work=================================
include(configure/CMakeLists.txt)

add_subdirectory("doc/man")
add_subdirectory("doc/info")
add_subdirectory("src/common")
add_subdirectory("src/det2nx")
add_subdirectory("src/detinfo")
add_subdirectory("src/mcaops")
add_subdirectory("src/nx2xml")
add_subdirectory("src/nxcat")
add_subdirectory("src/nxls")
#add_subdirectory("src/nxsh")
#add_subdirectory("src/nxtee")
add_subdirectory("src/xml2nx")

add_subdirectory("test")

