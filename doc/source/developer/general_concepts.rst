=========================
Common operation concepts
=========================

As many of the programs share a common philosophy of how they treat data it is
worth to read this section before continuing with the reading the man page of a
particular program. It will safe you a lot of time and make the man pages more
instructive to you when you read this first. 

Managing Regions of Interest (ROIs)
===================================

A region of interest (ROI) defines a particular region in a 1D or a 2D detector.
If a program offers you the possibility to the specify one or several ROIs,
whatever the program will do will be restricted to these ROIs.  ROIs are usually
passed to a program by the ``-r`` or ``--roi`` command line option. For
instance, if you are interested only in the data stored between channels 230 and
1025 of an MCA you can select this ROI with

.. code-block:: bash

   $> prog --roi=230:1026 ......some other options...
   
which will cause the program to act only on the data from channel 230 to 1024
(the last value of the ROI is not included).
For 2D data the ROI can be set with

.. code-block:: bash

   $> prog -r230:1026,100:512 .....some other options....
   
which will select data form pixel 230 to 1025 in the first and 100 to 511 in the
second dimension. In many cases you can pass several ROIs to the program. In
this case each ROI gets its own option. This is shown here for an MCA

.. code-block:: bash

   $> prog -r20:45 -r100:512 -r1024:1398 .....some other options...
   

Selecting files for input and output
====================================

In many cases a program acts on data stored in one or many files. The names of
files (usually used for input) are passed as command line arguments to the
program. In the simplest case you can just add the filename at the end of the
command line used to run the program

.. code-block:: bash

   $> prog ...options... input_file.dat
   
If many files should be passed to a program one can use wildcards like this

.. code-block:: bash
   
   $> prog ...options... data/may_2012/exp_*.dat
   
which will pass a list of command line arguments with all file names matching
the wildcar ``data/may_2012/exp_*.dat`` to the program. 
Until now we this is the behavior one would expect for any UNIX program. 
However, there is one case which needs a bit more care. 
In many cases you have to read a whole bunch of individual detector files into
your program. You might be tempted to use the wild card approach mentioned
before to do this. However, in this case you cannot be sure that the files are
passed in the appropriate order to your program. It depends on the shell how the
files are ordered if wild cards are used. 
In such a situation there are two approaches which can be used

* use the  ``--input`` option whose value is the name of a file containing the
  name of the files to read in the desired order
* use a template and a numeric range to specify the input files. 

The first approach is rather straight forward: write the name of the files to an
ASCII file (lets say files.txt)  and then use

.. code-block:: bash 
   
   $> prog --input=files.txt ...other options....

To tell the program which files to process. 

Though being very simple to understand using such an input file can be pretty
tedious in particular if the number of files is large. However, in many cases
where the order of the input files matters the filenames contain a number
determining the position of the file in the total list of files. 
Such a file typically looks like ``detector_may_2012_<NUMBER>.dat`` where
``<NUMBER>`` is the index of the file in the list. 
In such a case the files can be described using the following syntax

.. code-block:: bash

   $> prog ...options... detector_may_2012_%05i.dat:100:1000
   
This means that read all files following the pattern ``detector_may_2012_%05i.dat``
starting from ``detector_may_2012_100.dat`` until ``detector_may_2012_1000.dat``. 
Unlike for ROIs the last number is included. You can even do more sophisticated
things. Consider that you want only to read every second file from the list. In
this case the above example changes to

.. code-block:: bash

   $> prog ...options... detector_may_2012_%05i.dat:100:1000:2
   
In general this follows the following syntax

.. code-block:: text
       
   file_template:start:stop:stride
   
where ``file_template`` is a C-format string (for integers). This is possible
because a colon must not appear as a part of a file or path name (at least not
on Unix systems). 

Acessing objects in a Nexus file
================================

Nexus files can be considered as a file-system in a file. Nexus as used here is
assumed to use HDF5 as a storage backend. 
If we would like to access an object in a file we can use the following syntax

.. code-block:: bash

   prog file://path/to/object
   
attributes attached to an object can be described with

.. code-block:: bash
   
   prog file://path/to/object@attribute
   
This syntax works when you know the exact path to a particular object. Aside
from object names Nexus introduces the concept of base classes. Each object in
a Nexus file belongs to one of these base classes. One can thus refine the path
to an object to

.. code-block:: bash
   
   prog file://path:class_1/to:class_2/object:class_3
   
In this case no only the names of the different objects must match but also
they must belong to a particular base class. 
Finally, if we do not know the exact path but only the classes we can write the
path only in terms of base classes

.. code-block:: bash
   
   prog file://:class_1/:class_2/:class_3
   
In this case the different types must be unique. In case of ambiguities the
program will abort with an error message.

Input and output of multidimensional data
=========================================

In many cases multidimensional data is either written to a standard out 
or read from standard input (the canonical examples would be 
:program:`nxcat` and :program:`nxtee`). As NeXus can also handle 
multidimensional data we need a way to represent this on a console. 

Reading from standard input
---------------------------

On a console there are virtually only two dimensions. So whenever we have to 
deal with multidimensional data for reading it is considered 

.. math::

   s = \prod_{i=0}^{r-1} n_i
   
where :math:`n_i` is the number of elements along the :math:`i`-th dimension.
In order to indicate the start of a next data item we use a `\n`. 
In practive this means 

The data for a simple :math:`2\times 2` matrix would be a single stream 4 values 

.. text::

   1 21 32 23
   
For attributes this is all you can do. For datasets, however, we often have the 
situation that we want to write a time series of data values. In such a case 
the first dimension typically denotes time where the remaining dimensions 
are the actual dimension of the data element (except for scalar values
where there is no additional dimension). Consider we want to store a series
of the above  :math:`4\times 4` matrix. The dataset would have a a shape of
:math:`n\times 4 \times 4` where the first dimension is the time. If we  want
to store 3 entries in such a dataset the output on standard out should look like 
this 

.. text:: 

   1 21 33 243
   3 45 223  42
   38 -2 43 23
   
Each `\n` indicates a step forward along the first dimesion of the dataset. 
     

Wirting to standard output
--------------------------

Writing the data to standard output has a similar problem: we have only 
two dimensions available but may have to write data with more than two 
dimensions. 
Like for reading data a `\n` indicates a step along the first dimension 
of a dataset. The remaining dimensions (if there are any) are flattened into
a single dimension and the output . 


