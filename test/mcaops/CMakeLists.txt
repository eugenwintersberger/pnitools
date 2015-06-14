set(DATFILES mca_gauss.dat)


foreach(F ${DATFILES})
    configure_file(${F} ${F} COPYONLY)
endforeach()


