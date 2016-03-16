
nxls
====

Synopsis
--------

.. code-block:: text
    
    nxls [OPTIONS] NEXUSPATH 

Description
-----------

``nxls`` lists the content of a Nexus file. Like its Unix counter part
``ls``, ``nxls`` shows the content of the file relative to a particular
group within the file. In the simplest case this is the root group of the file. 
As the command line argument must be a valid Nexus path in no case the name of
the file alone will suffice. It is at least necessary to add the root part. 
In such a case a possible call of ``nxls`` would look like this

.. code-block:: bash

    $ nxls data.nxs://

By default ``nxls`` removes the leading part of the path of the individual 
Nexus objects. This is just to save space in the output. To obtain the full 
path use the ``-f`` option.

Options
-------
The programm takes the following options:

-h, --help  print short program help
-r, --recursive  show the content of all subgroups of a given Nexus group
-a, --show-attributes  shows attributes in addition to groups and field.
-f, --full-path  show the full path for each object
-l, --long  show additional information for each object

Examples
--------

.. code-block:: bash
    
    $ nxls data.nxs://

shows the content of the root group

.. code-block:: bash

    $ nxls -f data.nxs://:NXentry/:NXinstrument

lists all objects in the instrument group of the Nexus file with full path

.. code-block:: bash

    $ nxls -a data.nxs://:NXentry/:NXinstrument

lists all objects in the instrument group of the Nexus file including all 
attributes

.. code-block:: bash

    $ nxls -al data.nxs://:NXentry/:NXinstrument/:NXdetector/data

shows detailed information about the data field in the detector group

Return value
------------

0 in the case of success, 1 otherwise




