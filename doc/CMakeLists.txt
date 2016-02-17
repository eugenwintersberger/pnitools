add_subdirectory("source")
add_subdirectory("build")

add_subdirectory("man")
add_subdirectory("info")

configure_file(Makefile SphinxMakefile COPYONLY)
configure_file(Doxyfile Doxyfile @ONLY)
configure_file(DoxygenLayout.xml DoxygenLayout.xml COPYONLY)
configure_file(doxygroups.dox doxygroups.dox COPYONLY)

#here we have to build the code