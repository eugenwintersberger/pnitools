set(FILES mca.xml append.dat replace.dat counts.dat)

foreach(F ${FILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()

add_executable(nxtee_acceptance_test test.cpp $<TARGET_OBJECTS:test_config>)
target_link_libraries(nxtee_acceptance_test pniio 
    Boost::unit_test_framework Boost::filesystem)

add_boost_logging_test("nxtee:acceptance:test"
                       nxtee_acceptance_test
                       ${PROJECT_BINARY_DIR}/test/nxtee)
