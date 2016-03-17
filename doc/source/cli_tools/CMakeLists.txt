set(source_files datgen.rst
                 detinfo.rst
                 detops.rst
                 mcaops.rst
                 nxcat.rst
                 nxls.rst
                 xml2nx.rst
                 nxtee.rst
                 )

add_subdirectory(pics)

foreach(f ${source_files})
    configure_file(${f} ${f} COPYONLY)
endforeach()



