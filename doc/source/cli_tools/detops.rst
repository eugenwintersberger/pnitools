
detops
======

Synopsis
--------

Apply cumulative image operations on detector files

.. code-block:: bash

    detops COMMAND [OPTIONS] [FILE]

Description
-----------
``detops`` is a utility program applying certain operations on 2D detector data. 
The detector data can be read from one or several single image detector files.

All results are written to standard output. This allows several `mcaops``
commands to be chained using the pipe operator. 

The behavior of ``mcaops`` is controlled via the command string which is
passed as the first argument to the program.  Currently
the following commands are available:

=========  ======================================================
Command    Description
=========  ======================================================
**max**    find the value and its position in the spectrum
**sum**    add all value in the spectrum
**rebin**  rebin the spectrum to new bin sizes
**scale**  scale the bin centers of the spectrum
**dump**   dump channel and mca data unchanged to standard out
=========  ======================================================

These operations can roughly devided into two groups: accumulating and
non-accumulating operations. The former one reduces the entire MCA data to a
single number while the latter one preserves the spectrum character of the data
(though rebining maybe alters the number of bins). 

Options
-------
The  options provided and their meaning depend on the operation that should be
performed on the data. Some of of the options are global and valid for all
operations other are only defined for a particular command. 

Global options:

-h, --help  Print a usage message and exit.
-v, --verbose  Produce verbose output, printing information regarding the 
               specified options and objects.  All output is printed to 
               standard error allowing you to redirect payload data to an 
               other program while still watching debugging output.
-q, --quiet    Suppress all unnecessary output (the counterpart of -v)
--header       print a header before dumping the output to standard out
--xolumn=[COLNAME]  specify the name of the column to choose from the input 
                    to use as bin-center or -index values. This option is 
                    only useful when used in connection with FIO files.
--ycolumn=[COLNAME]  specify the name of the column to use for MCA data. 
                     This option is only useful with a FIO file. 


Options for the **rebin** operation:

-b, --binsize=[NBINS]  defines the number of bins that should be collated 
                       during rebining. 
--noxrebin  do not rebin the x-axis. Instead use indices for the output. 
--normalize  normalize the rebinned data.

Options for the  **scale** operation:

-c, --center=[CENTER]  defines the index of the center bin used for 
                       rescaling. 
-d, --delta=[DELTA]    defines the step width for the rebin operation
-x, --cvalue=[CENTERVALUE]  the value of the center bin.

The **sum** and **mmax** command have no additional options.

Return value
------------
0 in case of success and -1 otherwise. 

Examples
--------

Lets start with a very simple example reading data form standard input and using
the accumulating operations **sum** and **max**. For the sake of convenience 
a data file should be created which looks like this

.. code-block:: text

    0 1
    1 0
    2 10
    3 50
    4 100
    5 200
    6 70
    7 150
    8 20
    9 1
    10 0

and store the file as ``test.dat``. Here the first column is the channel 
index while the second holds the channel data. 
To compute the sum of the data stored use

.. code-block:: bash

    $ cat test.dat | mcaops sum 
    602

where the output, 602, is the sum of values stored in the second column.
Analogously, to find the maximum use

.. code-block:: bash

    $ cat test.dat | mcaops max
    5   200

the two  numbers are the position of the maximum and its value respectively. 

