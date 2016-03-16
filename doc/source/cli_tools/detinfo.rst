
detinfo
=======

Synopsis
--------
Prints detector information from files to standard output

.. code-block:: bash
    
    detinfo [OPTIONS] FILE [FILE ...]


Description
-----------

``detinfo`` prints information about detector data stored in files 
to standard output using various formats.
Currently ``detinfo`` supports the following file formats:

* CBF - the DECTRIS flavor used for Pilatus detectors
* TIF - used by many other detectors to hold data
* Nexus using HDF5 as a storage backend.

The parameters ``detinfo`` retrieves are 

* the path to the data (file path and/or Nexus object path)
* the number of frames stored in the file or NXdetector group
* the number of elements along each dimension of a single detector frame
* the pixel data type
* the detector type

Possible detector types are *point*, *linear*, and *area*.

For TIF and CBF files ``detinfo`` assumes that all the data in a file belongs
to a single detector. However, Nexus files are slightly different as they can
store data from several detectors in a single file. In this case, the
information listed above is shown for each instance of *NXdetector* available in
the file.  A typical application of ``detinfo`` would be to gather all the
information required to merge data from single TIF or CBF files into a Nexus
file.  As with all programs from the *pni-tools*-package input files can be
specified as individual files and/or as a file template with a numeric range.
For details see the info page for pni-tools how to do this.

Options
-------

The programm takes the following options:

-h, --help      print short program help
-f, --format    select the output format. Currently this option can take 
                the following values

                ============ =================================
                Format       Description
                ============ =================================
                ``simple``   producing simple output 
                ``csv``      format output as CSV table 
                ``keyvalue`` format output as key-value pairs
                ``xml``      format output as XML
                ============ =================================


Return value
------------
0 in the case of success, 1 otherwise

Author
------
Written bei Eugen Wintersberger <eugen.wintersberger@desy.de>

