set(DATFILES test_sum.py
             fiodata.nxs
             total_sum.dat
             roi1_sum.dat
             roi2_sum.dat
    )


foreach(F ${DATFILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()


