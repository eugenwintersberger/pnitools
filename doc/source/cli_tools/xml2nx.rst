
xml2nx
======


Synopsis
--------

.. code-block:: text

    xml2nx [OPTIONS] FILE [FILE ...]


Description
-----------

``xml2nx`` converts XML files holding NXDL content to Nexus files. This
program can be used to create fields and groups in a Nexus file on the basis of
an NXDL file. It thus might be useful for systems using the shell as their
operating environment. 

The NXDL file does not necessarily need to contain the full file structure. It
is even possible to add only a particular base class or component to the file. 
This is particularly useful if one wants to play with different components.

Options
-------

The programm takes the following options:

-h, --help  print short program help
-p, --parent  The parent node under which the content described by the NXDL 
              file should be attached. 
-o, --overwrite  Overwrite the file. With this option set an already 
                 existing file of same name will be overwritten.

Return value
------------
0 in the case of success, 1 otherwise




