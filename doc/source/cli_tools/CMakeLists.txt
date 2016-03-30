set(source_files 
                 detinfo.rst
                 detops.rst
                 mcaops.rst
                 nxcat.rst
                 nxls.rst
                 xml2nx.rst
                 nx2xml.rst
                 nxtee.rst
                 )

add_subdirectory(pics)

foreach(f ${source_files})
    configure_file(${f} ${f} COPYONLY)
endforeach()



