
configure_file(readme.txt readme.txt COPYONLY)
configure_file(download.sh download.sh COPYONLY)

add_custom_command(OUTPUT pnitools-test-data.tar.gz
                   COMMAND ./download.sh
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   COMMENT "Download test data ...")
add_custom_target(download_data ALL DEPENDS pnitools-test-data.tar.gz)

add_custom_command(OUTPUT fio
                   COMMAND tar -xzf pnitools-test-data.tar.gz
                   DEPENDS download_data
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   COMMENT "Unpack test data ...")

add_custom_target(gather_test_data ALL
                  DEPENDS fio)
                   

