cmake_minimum_required(VERSION 3.0)
project(pnitools
        LANGUAGES CXX C
        VERSION 1.1.0)
include(CTest)
set(CMAKE_CXX_STANDARD 11)

include(CPackComponent)

#==============================================================================
# load some default configuration
#==============================================================================
include(cmake/common/EnsureBuildType.cmake)
include(cmake/common/InstallConfig.cmake)
include(cmake/common/WindowsUtils.cmake)


set(WITH_CONAN OFF CACHE BOOL "Satisfy depdencies from conan")
if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set(WITH_CONAN ON)
endif()

if(WITH_CONAN)
    include(cmake/common/ConanSetup.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/conan.cmake)
    
    conan_cmake_run(CONANFILE conanfile.txt
    	            BASIC_SETUP
    	            BUILD missing)
endif()

#======================do here some setup work=================================
include(configure/CMakeLists.txt)


#add_subdirectory("doc")
add_subdirectory("src/common")
add_subdirectory("src/detinfo")
#add_subdirectory("src/detops")
if(NOT CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    #add_subdirectory("src/mcaops")
endif()
add_subdirectory("src/nxcat")
add_subdirectory("src/nxls")
add_subdirectory("src/nxtee")
add_subdirectory("src/xml2nx")
add_subdirectory("src/datgen")

add_subdirectory("test")
add_subdirectory("resources")

#=============================================================================
# generate package here
#=============================================================================
if(CMAKE_HOST_SYSTEM MATCHES Windows)
    MESSAGE(STATUS "================setting up packaging====================")

    set(ASSEMBLY_DIR "desy.fsec.pnitools")
    set(ASSEMBLY_MANIFEST "desy.fsec.pnitools.manifest")

    #first we need to locate all the library files
    install(DIRECTORY ${PROJECT_BINARY_DIR}/bin/${ASSEMBLY_DIR}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
            PATTERN "*.exe" EXCLUDE
            PATTERN "*.manifest" EXCLUDE
            PATTERN "*"
            )
    configure_file(desy.fsec.pnitools.manifest.in bin/${ASSEMBLY_DIR}/${ASSEMBLY_MANIFEST}
        @ONLY)
    install(FILES ${PROJECT_BINARY_DIR}/bin/${ASSEMBLY_DIR}/${ASSEMBLY_MANIFEST}
        DESTINATION ${CMAKE_INSTALL_BINDIR}/${ASSEMBLY_DIR}
        )


    set(CPACK_GENERATOR WIX)
    set(CPACK_PACKAGE_VENDOR "DESY")
    set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

    set(CPACK_WIX_PRODUCT_ICON "resources/icon.ico")
    set(CPACK_WIX_UI_BANNER "resources/banner.bmp")
    set(CPACK_WIX_UI_DIALOG "resources/ui_dialog.bmp")
    set(CPACK_RESOURCE_FILE_LICENSE ${PROJECT_SOURCE_DIR}/LICENSE.txt)

    set(CPACK_WIX_PATCH_FILE ${PROJECT_SOURCE_DIR}/WIXSetPath.wxs)

#    cpack_add_component(Runtime
#        DISPLAY_NAME "Runtime files"
#        DESCRIPTION "Binaries"
#        GROUP "Runtime")
    
    include(CPack)
    include(CPackWIX)

endif()
