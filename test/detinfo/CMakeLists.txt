set(FILES detinfo_test.py __init__.py)

foreach(F ${FILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()
