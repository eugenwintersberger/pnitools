set(FILES mca.xml nxtee_test.py)

foreach(F ${FILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()


