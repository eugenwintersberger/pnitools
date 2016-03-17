
.. _nexus_path-label:

NeXus path
==========

The internal structure of a NeXuS file resembles loosely that of a Unix file
system. Fields (which are the primary objects for storing numerical data in
NeXuS) are organized in groups and can be addressed by an Unix like path like
this

.. code-block:: bash

    $ prog file://path/to/object

The filename is separated from the object path by ``://`` everything
afterwards refers to objects within the file. A NeXus path differs from a
common Unix filesystem path by two aspects

* groups and fields can have additional attributes to store meta-data
* groups (which would be the equivalent to a directory on a filesystem)
  can have a particular type which adds semantics to the fields stored 
  in the group. In NeXus terminology the type of a group is also referred 
  as the `class` a group belongs to.

To access attributes attached to a group or field just add the name of the 
attribute to path with a leading `@`

.. code-block:: bash

    $ prog file://path/to/object@attribute

Dealing with the `class` of a group is a bit more complex. The `class` a NeXus
group belongs to gives meaning (semantics) to the fields and groups stored
within it. Consider, for instance, a group of `class` *NXdetector* which stores 
data for detector data. Whenever a program enters such a group it can expect
certain fields to be present and also knows what kind of data every field
holds. See the `NXdetector definition`_ for the fields defined for this
particular `class`. 
A complete overview over all classes available in the NeXus standard  
can be obtained from the `NeXus Class Definitions`_-website. 

The `class` a group must belong to can be described in the NeXus path by 
appending the `class` name to a group name separated by a ``:``. 
Consider the  following example

.. code-block:: bash

    $ prog file.nxs://scan_1:NXentry/beamline:NXinstrument/pilatus:NXdetector


From this path we can easily determine to which `class` every group in the path
must belong to

==========  ============
Group name  Class
==========  ============
scan_1      NXentry
beamline    NXinstrument
pilatus     NXdetector
==========  ============

The concept of a `class` allows it to write a generic path for a particular
application as we can omit the name of a group in the path and just use the 
`class`. We can rewrite the above example with 

.. code-block:: bash

    $ prog file.nxs://:NXentry/:NXinstrument/:NXdetector

Such a path is generic as we do not have to know the exact names of the
particular elements. If data files are designed carefully according to the
NeXus standard we can use this generic path on any file without caring about
the names of objects.
The only restriction we have is that there is only a single instance of each
`class` at its level of the NeXus tree.

.. _NXdetector definition: http://download.nexusformat.org/doc/html/classes/base_classes/NXdetector.html
.. _NeXus Class Definitions: http://download.nexusformat.org/doc/html/classes/index.html
