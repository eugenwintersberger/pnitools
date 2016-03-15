set(RSTFILES index.rst 
             command_line_tools.rst
             developer_documentation.rst
             det2nx.rst)


add_subdirectory("_static")
add_subdirectory("_templates")
add_subdirectory("developer")
configure_file(conf.py conf.py COPYONLY)


foreach(RSTFILE ${RSTFILES})
    configure_file(${RSTFILE} ${RSTFILE} COPYONLY)
endforeach()