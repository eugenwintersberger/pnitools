set(RSTFILES general_concepts.rst
             common_code.rst
             nxls_devel.rst
             nxtee_devel.rst
             mcaops_devel.rst
)

foreach(RSTFILE ${RSTFILES})
    configure_file(${RSTFILE} ${RSTFILE} COPYONLY)
endforeach()