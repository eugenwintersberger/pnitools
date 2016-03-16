
nxcat
=====

Synopsis
--------
output scalar data from a Nexus file

.. code-block:: text

    nxcat [OPTIONS] SOURCE [SOURCE ...]

Description
-----------

``nxcat`` prints the output of one or more fields stored in Nexus files to
standard out. The fields are specified by Nexus paths. For more information
about Nexus path notation have a look at

Options
-------

The programm takes the following options:

-h, --help   print short program help
--header     Print header with column name and unit information to the output.
-s, --start  first index
-e, --end    last index

Return value
------------
0 in the case of success, 1 otherwise




