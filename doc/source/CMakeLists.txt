set(RSTFILES index.rst 
             command_line_tools.rst
             developer_documentation.rst
             general_concepts.rst
             installation.rst
             overview.rst
             det2nx.rst)


add_subdirectory("_static")
add_subdirectory("_templates")
add_subdirectory("developer")
add_subdirectory("cli_tools")
add_subdirectory("general_concepts")
configure_file(conf.py conf.py COPYONLY)


foreach(RSTFILE ${RSTFILES})
    configure_file(${RSTFILE} ${RSTFILE} COPYONLY)
endforeach()
