
.. _determining-input-files:

Determining input files
=======================

Many programs provided by **pnitools** work with data stored in one ore several
files and expect the name(s) of the input file(s) as arguments at the end of
the command line call.
Thus, for a single input file a typical command line call can be expected to
be of the form

.. code-block:: bash

    $ prog [OPTIONS] input_file.dat

If supported by the executing shell, wildcards can be used to pass an
entire list of files to a program like this

.. code-block:: bash

    $ prog [OPTIONS] data/may_2012/exp_*.dat

Using wildcards to determine a large number of files works quite well as long
as the order in which the files are processed by the program does not matter.
The order, in which the filenames appear after the expansion of the wildcard
depends, on two factors

* the executing shell
* the structure of the filenames. 

Most shells provided the filenames in lexicographical use a lexicographical
order after wildcard expansion.  However, in general, one cannot make any
assumption about the order in which the filenames appear. As this is
problematic in situations where the order of the input files matters there are
basically two ways of how to approach this issue

* one can provide a file with the names of the files to process in appropriate
  order and pass it to the program via the option :option:`--input`

    .. code-block:: bash

        $ prog --input=input_files.txt [OPTIONS]

* or use a format string and a numeric range to determine the input files. 

The first approach is rather straight forward: write the names of the files to
an ASCII file and pass this file via the :option:`--input` to the program.  One
of the advantage is that the filenames stored in the input file must not match
any particular pattern.
You can pass whatever files you want. The obvious drawback of this method is
that one first has to generate the file :file:`input_files.txt` with the
filenames. This can become expensive if the number of input files is getting large.
Thus, for the *pnitools* package we have chosen the second approach. 

Fortunately, many applications that produce a large series of files
use a simple name pattern for their output files. These patterns typically
include the index of the file within the entire series. 
Usually such files are of the form :file:`detector_may_2012_<NUMBER>.dat` where
``<NUMBER>`` is the index of the file in the series. All programs in the
**pnitools** distribution that accept a series of input files support a special
syntax to handle such cases.
In its most general form this syntax reads

    FILEPREFIX , NUMBERFORMAT , FILESUFFIX , ":" , NUMERIC_RANGE

where *NUMBERFORMAT* is a C-style integer format as used for instance by
:command:`printf` and *NUMERIC_RANGE* is an integer (see
:ref:`numeric_ranges-label`).

How this exactly works can easily be shown by means of an example

.. code-block:: bash
    
    $ prog [OPTIONS] detector_may_2012_%05i.dat:100:1000

Where

+-----------------+----------------------+
| *FILEPREFIX*    | `detector_may_2013_` | 
+-----------------+----------------------+
| *NUMBERFORMAT*  | `%05i`               | 
+-----------------+----------------------+
| *FILESUFFIX*    | `.dat`               |
+-----------------+----------------------+
| *NUMERIC_RANGE* | `100:1000`           |
+-----------------+----------------------+

Thus, the above file series specifier represents a series of files starting
with :file:`detector_may_2013_000100.dat` and ending with
:file:`detector_may_2012_00999.dat`.  The above file selection can still be
refined by using a stride for in the numeric range

.. code-block:: bash

    $ prog OPTIONS detector_may_2012_%05i.dat:100:1000:2

This will basically produce the same list of filenames but but with a stride of
2 in the numbers meaning

.. code-block:: bash
    
    detector_may_2012_00100.dat
    detector_may_2012_00102.dat
    detector_may_2012_00104.dat
    .....
    detector_may_2012_00998.dat


This approach could be used in cases where every second image is a darkfield
which should not be processed by the software.

