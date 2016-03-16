
Determining input files
=======================

Many programs provided by **pnitools** work with data stored in one ore several
files. Most programs expect the names of input files to be passed as 
arguments at the end of their command line call.
Thus, for a single input file a typical command line call can be expected to
be of the form

.. code-block:: bash

    $ prog [OPTIONS] input_file.dat

j
If supported by the executing shell, wildcards can be used to pass an
entire list of files to a program. The command line

.. code-block:: bash

    $ prog [OPTIONS] data/may_2012/exp_*.dat


will pass all files to the program, whose name matches the pattern
:file:`data/may_2012/exp_*.dat`. The latter approach works quite well as long
as the order in which the files are processed by the program does not matter.
As the ordering in which the filenames appear after expansion of the wildcard
depends on the used shell one cannot make any assumptions about it.  There are
basically two approaches to handle such cases

* provide a file with the names of the files to process in appropriate order 
  and pass it to the program via the option :option:`--input`
* use a format string and a numeric range to determine the input files. 


The first approach is rather straight forward: write the names of the
files to an ASCII file and pass this file via the :option:`--input` to the
program

.. code-block:: bash

    $ prog --input=input_files.txt [OPTIONS]

this approach is not only simple to understand it also has the advantage that
the filenames stored in the input file must not match any particular pattern.
You can pass whatever files you want. The obvious drawback of this method is
that one first has to generate the file :file:`input_files.txt` with the
filenames. This can become expensive if the number of input files is large.

Fortunately, many applications that produce a large series of files
use simple file name patterns for their output files. These patterns typically
include the index of the file in the entire series. 
Usually such files are of the form :file:`detector_may_2012_<NUMBER>.dat` where
``<NUMBER>`` is the index of the file in the series. All programs in the
**pnitools** distribution that accept a series of input files support a special
syntax to handle such cases.

In its most general form this syntax reads
    [FILEPREFIX]%[NUMBERFORMAT][FILESUFFIX]:[NUMERIC RANGE]

where [NUMBERFORMAT] is a C-style integer format as used for instance by
@command{printf} and [NUMERIC RANGE] is an integer range. 
The best way to understand this syntax is via an example like this

.. code-block:: bash
    
    $ prog [OPTIONS] detector_may_2012_%05i.dat:100:1000

Here the [FILEPREFIX] is `detector_may_2012_`, the number format is given
by `%05i`, the [FILESUFFIX] is `.dat`, and the numeric
range is `100:1000`.  Thus, the above file series specifier represents a
series of files starting with
:file:`detector_may_2013_000100.dat` and ending with
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


With this one would be able to omit dark-field images recorded after every
sample image.

