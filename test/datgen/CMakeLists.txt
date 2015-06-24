set(FILES datgen_global_test.py
          datgen_uniform_test.py
          datgen_linear_test.py
          __init__.py)

foreach(F ${FILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()
