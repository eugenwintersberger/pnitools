set(SOURCE gnuplot.pdf
           gnuplot.png
           mca_basics_1.pdf
           mca_basics_1.png
           mcaops_rebin3.pdf
           mcaops_rebin3.png
           mcaops_test1_dat.pdf
           mcaops_test1_dat.png
           mcaops_test1_dat.txt
           mcaops_testdata.pdf
           mcaops_testdata.png
           mcaops_testdata.txt
           mcaops_test_dat.pdf
           mcaops_test_dat.png
           mcaops_test_dat.txt
           nxcat_full.pdf
           nxcat_full.png
           nxcat_selection.pdf
           nxcat_selection.png
           nxtee_append.png
           nxtee_replace.png
           datgen_example_1.png
           datgen_example_2.png
           )

foreach(IMAGE ${SOURCE})
    configure_file(${IMAGE} ${IMAGE} COPYONLY)
endforeach()
