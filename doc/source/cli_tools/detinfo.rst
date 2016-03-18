
detinfo
=======

Synopsis
--------
Prints detector information from files to standard output

.. code-block:: bash
    
    detinfo [OPTIONS] FILESPEC [FILESPEC ...]


Description
-----------

:program:`detinfo` prints information about detector data stored in files 
to standard output using various formats. A typical application for this 
program is to determine the parameters of a bunch of detector files 
before merging them together into a single NeXus file.
Currently :program:`detinfo` supports the following file formats:

* CBF - the DECTRIS flavor used for Pilatus detectors
* TIF - used by many other detectors to hold data
* Nexus - using HDF5 as a storage backend.

:program:`detinfo` provides information about

* the path to the data (file path and/or Nexus object path)
* the number of frames stored in a file or an *NXdetector* group in case of a
  NeXus file
* the number of elements along each dimension of a single detector frame
* the data type of a single pixel
* the detector type, possible types are *point*, *linear*, and *area* denoting
  0-, 1-, and 2-dimensional detectors respectively.

For TIF and CBF files :program:`detinfo` assumes that all the data in a file
belongs to a single detector. Nexus files are treated differently as they can
store data from several detectors in different instances of *NXdetector* in a
single file. In this case, the information listed above is shown for each
instance of *NXdetector* available in the file. 
See :ref:`determining-input-files` for how to describe input files. 

Options
-------

The output of :program:`detinfo` can be controlled by means of the following
options

.. option:: -h, --help      

   print short program help

.. option:: -f, --format    


   select the output format. Currently this option can take the following
   values

   ============ =================================
   Format       Description
   ============ =================================
   ``simple``   simple tabular output (default)
   ``csv``      format output as CSV table 
   ``keyvalue`` format output as key-value pairs
   ``xml``      format output as XML
   ============ =================================

Examples
--------

Consider a directory with TIF files, calling :program:`detinfo` with no options
would yield a result similar to this

.. code-block:: bash

    $ detinfo detector_%03i.tif:9:16
    detector_009.tif  type = area  pixel type = UINT32  frames = 1 frame shape = (2300,2300)
    detector_010.tif  type = area  pixel type = UINT32  frames = 1 frame shape = (2300,2300)
    detector_011.tif  type = area  pixel type = UINT32  frames = 1 frame shape = (2300,2300)
    detector_012.tif  type = area  pixel type = UINT32  frames = 1 frame shape = (2300,2300)
    detector_013.tif  type = area  pixel type = UINT32  frames = 1 frame shape = (2300,2300)
    detector_014.tif  type = area  pixel type = UINT32  frames = 1 frame shape = (2300,2300)
    detector_015.tif  type = area  pixel type = UINT32  frames = 1 frame shape = (2300,2300)

``csv`` output for the same directory 

.. code-block:: bash

    $ detinfo -fcsv detector_%03i.tif:9:16
    source ; type ; pixel type ; number of frames ; frame shape
    detector_009.tif ; area ; UINT32 ; 1 ; (2300,2300)
    detector_010.tif ; area ; UINT32 ; 1 ; (2300,2300)
    detector_011.tif ; area ; UINT32 ; 1 ; (2300,2300)
    detector_012.tif ; area ; UINT32 ; 1 ; (2300,2300)
    detector_013.tif ; area ; UINT32 ; 1 ; (2300,2300)
    detector_014.tif ; area ; UINT32 ; 1 ; (2300,2300)
    detector_015.tif ; area ; UINT32 ; 1 ; (2300,2300)

The ``csv`` output could be used for automatic processing of the output. 
Note that the first row of output contains the column names 
:program:`detinfo` associates each entry with.

A Nexus file can store the data of several detectors and the full path to the
data field of every detector is used as the source 

.. code-block:: bash

    $ detinfo  tstfile_00012.h5
    tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_1:NXdetector/data\
    type = point  pixel type = UINT64  frames = 2001 
    tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_10:NXdetector/data\
    type = point  pixel type = UINT64  frames = 2001 
    tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_2:NXdetector/data\
    type = point  pixel type = UINT64  frames = 2001 
    tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_3:NXdetector/data\
    type = point  pixel type = UINT64  frames = 2001 
    tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_4:NXdetector/data\
    type = point  pixel type = UINT64  frames = 2001 
    tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_5:NXdetector/data\
    type = point  pixel type = UINT64  frames = 2001 
    tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_6:NXdetector/data\
    type = point  pixel type = UINT64  frames = 2001 
    tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_7:NXdetector/data\
    type = point  pixel type = UINT64  frames = 2001 
    tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_8:NXdetector/data\
    type = point  pixel type = UINT64  frames = 2001 
    tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_9:NXdetector/data\
    type = point  pixel type = UINT64  frames = 2001

Not that in the case of a point detector no frame shape is shown.

Return value
------------
0 in the case of success, 1 otherwise

Author
------
Written by Eugen Wintersberger <eugen.wintersberger@desy.de>

