
NeXus path
==========

The internal structure of a NeXuS file resembles loosely that of a Unix file
system. Fields (which are the primary objects for storing numerical data in
NeXuS) are organized in groups and can be addressed by an Unix like path like
this

.. code-block:: bash

    $ prog file://path/to/object

The filename is separated from the object path by ``://`` everything
afterwards refers to objects within the file. The In addition to groups and
fields the Nexus path syntax allows also to address attributes

.. code-block:: bash

    $ prog file://path/to/object@attribute

The name of the attribute is indicated by the `@` symbol after the path
to the object to which it is attached to.

Unlik on a Unix filesystem where all directories are basically the same NeXus
adds some additional semantic information to a group by giving it a type.
A groups type indicates what kind of data is stored in this group. A group of
type *NXdetector*, for instance, stores detector related data. The types
correspond to NeXuS base classes which can be found in the NeXuS reference
manual.A base class defines a set of fields along with their names and physical
meaning. If we stay with the above example of the *NXdetector* type, the
*NXdetector* specification defines a field *data* within an 
instance of *NXdetector* which is intended to store the data recorded
by a detector.
With group types (base classes) at hand one can refine a path so that each
element must not only be of a particular name but also of a particular type as
in the next example 

.. code-block:: bash

    $ prog file://path:class_1/to:class_2/object:class_3

Each element of the path (except for the filename) has the form *name:class*.
The group types add an additional degree of freedom when writing a path.
Consider the case where an instance of a particular type appears only once
within its parent. In this case we can omit the names entirely and write the
above path like this

.. code-block:: bash

    $ prog file://:class_1/:class_2/:class_3

Such a path is generic as we do not have to know the exact names of the
particular elements. If data files are designed carefully according to the
NeXus standard we can use this generic path on any file without caring about
the names of objects.

