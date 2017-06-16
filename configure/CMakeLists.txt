include(CheckTypeSize)
include(CheckCXXSourceCompiles)

find_package(PythonInterp)
if(NOT PYTHONINTERP_FOUND)
    message(FATAL_ERROR "Could not find Python executable")
endif()


find_package(HDF5 REQUIRED)

find_package(pnicore REQUIRED)

find_package(pniio REQUIRED)

find_package(Boost 1.55 REQUIRED COMPONENTS unit_test_framework)

link_directories(${Boost_LIBRARY_DIRS})
add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})

#setup for GNU CXX compiler
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    message("found GNU compiler ...")
    if(CMAKE_BUILD_TYPE MATCHES RELEASE)
        message("setup for release build ...")
        add_definitions(-O3)
    elseif(CMAKE_BUILD_TYPE MATCHES DEBUG)
        message("setup for debug build ...")
        add_definitions(-O0 -g)
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    add_definitions(-DBOOST_ALL_DYN_LINK)
endif()

#===================================check the size of data types===============
include(configure/CheckTypeSize.txt)
