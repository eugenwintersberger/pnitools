include(CheckTypeSize)
include(CheckCXXSourceCompiles)



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

endif()

find_package(pnicore REQUIRED)

find_package(pniio REQUIRED)

find_package(Boost 1.55 COMPONENTS unit_test_framework)


#===================================check the size of data types===============
include(configure/CheckTypeSize.txt)
