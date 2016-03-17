
nx2xml
======


Synopsis
--------

.. code-block:: bash

    $ nx2xml [OPTIONS] FILE [FILE...]

Description
-----------

:program:`nx2xml` dumps the structure of a Nexus file as XML to standard out or
to an output file.  The output of the program is most probably not fully NXDL
compliant. In addition the current version can have some issues with files
written with the original C-Nexus API provided by the NIAC. In the current
version the output includes some scalar data which might be useful. However,
this will in future be only available via command line options. 

Program options
---------------

The programm takes the following options:

.. option:: -h, --help

   print short program help

.. option:: -o, --output

   output file where the XML content will be stored

Examples
--------

A basic example would look like this

.. code-block:: bash

   $ nx2xml output.nx

leads to

.. code-block:: xml

    <?xml version="1.0" encoding="utf-8"?>
    <group name="/" type="">
        <group name="scan_1" type="NXentry">
            <group name="control" type="NXmonitor"/>
            <group name="data" type="NXdata"/>
            <group name="instrument" type="NXinstrument">
                <group name="detector" type="NXdetector">
                    <field name="data" type="uint32">
                        <dimensions rank="2">
                            <dim index="1" value="0"/>
                            <dim index="2" value="2048"/>
                        </dimensions>
                        <attribute name="long_name" type="string">detector raw data</attribute>
                        <attribute name="units" type="string">cps</attribute>
                    </field>
                    <field name="description" type="string">
                        PSD
                        <dimensions rank="1">
                            <dim index="1" value="1"/>
                        </dimensions>
                    </field>
                    <field name="distance" type="float32">
                        <dimensions rank="1">
                            <dim index="1" value="1"/>
                        </dimensions>
                    </field>
                    <field name="layout" type="string">
                        linear
                        <dimensions rank="1">
                            <dim index="1" value="1"/>
                        </dimensions>
                    </field>
                    <field name="x_pixel_size" type="float32">
                        <dimensions rank="1">
                            <dim index="1" value="1"/>
                        </dimensions>
                    </field>
                    <field name="y_pixel_size" type="float32">
                        <dimensions rank="1">
                            <dim index="1" value="1"/>
                        </dimensions>
                    </field>
                </group>
            </group>
            <group name="sample" type="NXsample"/>
        </group>
        <attribute name="HDF5_version" type="string">1.8.8</attribute>
        <attribute name="NeXus_version" type="string">4.3.0</attribute>
        <attribute name="file_name" type="string">output.nx</attribute>
        <attribute name="file_time" type="string">2013-08-28T11:23:21.779941+0200</attribute>
        <attribute name="file_update_time" type="string">2013-08-28T11:26:17.770658+0200</attribute>
    </group>

To store the output to a file use the :option:`--output` option

.. code-block:: bash

    $ nx2xml -ofile.xml output.nx

