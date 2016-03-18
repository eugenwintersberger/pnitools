
detops
======

Synopsis
--------

.. code-block:: bash

    detops [OPTIONS] FILESPEC [FILESPEC, ...]

Description
-----------
:program:`detops` is a utility program applying accumulative operations on 2D
detector data.  The detector data can be read from one or several single image
detector files.  Currently the following file formats are supported 

* CBF - DECTRIS style CBF files used for Pilatus detectors
* TIF - tagged image format

Input files can be specified as described in
:ref:`determining-input-files`.

:program:`detops` provides the following operations

=======  =============================================================
Command  Description
=======  =============================================================
*sum*    compute the sum of all pixels of the detector or selected ROI 
*max*    get maximum value of the entire detector or the selected ROI
*min*    get minimum value of the entire detector or the selected ROI
=======  =============================================================

All operations can be restricted to a single region of interest (ROI) by using
the :option:`--roi` option.


Options
-------

.. option:: -h, --help

   Print a short program help.

.. option:: -c, --command

   This option determines the operation executed on the image. It can be either
   *sum*, *min*, or *max*

.. option:: -r, --roi

   Can be used to pass a ROI (currently only a single ROI can be used) to the
   program. So the operation determined by :option:`--command` will only be 
   applied to the ROI instead of the entire detector.

Examples
--------

Return value
------------
0 in case of success and -1 otherwise. 
