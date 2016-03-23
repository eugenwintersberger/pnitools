
nxls
====

Synopsis
--------

.. code-block:: text
    
    nxls [OPTIONS] NEXUSPATH 

Description
-----------

:program:`nxls` lists the content of a Nexus file. Like its Unix counter part
:command:`ls`, :program:`nxls` shows the content of the file relative to a particular
group within the file. In the simplest case this is the root group of the file. 
As the command line argument must be a valid Nexus path in no case the name of
the file alone will suffice. It is at least necessary to add the root part. 
In such a case a possible call of :program:`nxls` would look like this

.. code-block:: bash

    $ nxls data.nxs://

By default :program:`nxls` removes the leading part of the path of the
individual Nexus objects in order to save space on the terminal. To obtain the
full path use the :option:`--full-path` option.

Options
-------
The program takes the following options:

.. option:: -h, --help  

   print short program help

.. option:: -r, --recursive  

   show the content of all subgroups of a given Nexus group

.. option:: -a, --show-attributes  

   shows attributes in addition to groups and field.

.. option:: -f, --full-path  

   show the full path for each object

.. option:: -l, --long  
 
   show additional information for each object

Examples
--------
In the simplest case we want to list all the object below the root group of the
file. This can be achieved with 

.. code-block:: bash

    $ nxls nxls_test.nxs://
    entry:NXentry

Note the `://` after the filename which is required to obtain a full NeXus
path. In addition one should recognize that the leading `/` in the output is
removed as all the output is relative to the root group. 
In this example only those objects residing directly below the root group are
shown.
For a recursive list through all the children of a particular group we have to 
add the :option:`--recursive` 

.. code-block:: bash

    $ nxls -r nxls_test.nxs://:NXentry/:NXinstrument
    detector:NXdetector
    detector:NXdetector/data
    detector:NXdetector/description
    detector:NXdetector/distance
    detector:NXdetector/layout
    detector:NXdetector/x_pixel_size
    detector:NXdetector/y_pixel_size
    name
    source:NXsource
    source:NXsource/name
    source:NXsource/probe
    source:NXsource/type

To obtain a full path for each object we have to add the :option:`--full-path`
option

.. code-block:: bash

    $ nxls -rfa nxls_test.nx://:NXentry/:NXinstrument
    /entry:NXentry/instrument:NXinstrument/detector:NXdetector
    /entry:NXentry/instrument:NXinstrument/detector:NXdetector@NX_class
    /entry:NXentry/instrument:NXinstrument/detector:NXdetector/data
    /entry:NXentry/instrument:NXinstrument/detector:NXdetector/data@units
    /entry:NXentry/instrument:NXinstrument/detector:NXdetector/description
    /entry:NXentry/instrument:NXinstrument/detector:NXdetector/distance
    /entry:NXentry/instrument:NXinstrument/detector:NXdetector/distance@units
    /entry:NXentry/instrument:NXinstrument/detector:NXdetector/layout
    /entry:NXentry/instrument:NXinstrument/detector:NXdetector/x_pixel_size
    /entry:NXentry/instrument:NXinstrument/detector:NXdetector/x_pixel_size@units
    /entry:NXentry/instrument:NXinstrument/detector:NXdetector/y_pixel_size
    /entry:NXentry/instrument:NXinstrument/detector:NXdetector/y_pixel_size@units
    /entry:NXentry/instrument:NXinstrument/name
    /entry:NXentry/instrument:NXinstrument/name@short_name
    /entry:NXentry/instrument:NXinstrument/source:NXsource
    /entry:NXentry/instrument:NXinstrument/source:NXsource@NX_class
    /entry:NXentry/instrument:NXinstrument/source:NXsource/name
    /entry:NXentry/instrument:NXinstrument/source:NXsource/name@short_name
    /entry:NXentry/instrument:NXinstrument/source:NXsource/probe
    /entry:NXentry/instrument:NXinstrument/source:NXsource/type

The additional :option:`--show-attributes` adds also all attributes to the
output.  If more information on stored objects is required the :option:`--long`
can be used 

.. code-block:: bash

    $> nxls -l nxls_test.nxs://:NXentry/:NXinstrument/:NXdetector
    FIELD   UINT32  (0,2048)    data
    ATTRIB  STRING  (1) data@units
    FIELD   STRING  (1) description
    FIELD   FLOAT32 (1) distance
    ATTRIB  STRING  (1) distance@units
    FIELD   STRING  (1) layout
    FIELD   FLOAT32 (1) x_pixel_size
    ATTRIB  STRING  (1) x_pixel_size@units
    FIELD   FLOAT32 (1) y_pixel_size
    ATTRIB  STRING  (1) y_pixel_size@units

The first column in the output describes the type of the object, the second the
data type, and the third the shape. The latter two columns are only used for
fields and attributes. 

Return value
------------

0 in the case of success, 1 otherwise




