set(source_files input_files.rst
                 nexus_path.rst
                 numeric_ranges.rst
                 rois.rst)


foreach(f ${source_files})
    configure_file(${f} ${f} COPYONLY)
endforeach()
