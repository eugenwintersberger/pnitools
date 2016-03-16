
Describing regions of interest (ROIs)
=====================================

A region of interest (ROI) defines a particular index region multidimensional
data.
Programs which allow the user to specify one or more ROIs
typically provide a :option:`-r` or :option:`--roi` command line option. 
The value of this option is a numeric range describing the indices of the data
which the ROI should include.
For instance, if you are interested only in the data stored between channels 230
and 1025 of an MCA you can select this ROI with

.. code-block:: bash

    $ prog --roi=230:1026 [OTHER OPTIONS]

which will cause the program to act only on the data from channel 230
to 1025. 

For 2D data the ROI can be set with

.. code-block:: bash

    $ prog -r230:1026,100:512 [OTHER OPTIONS]

which will select data form pixel 230 to 1025 in the first and 100 to
511 in the second dimension. In many cases you can pass several ROIs to the
program. In this case each ROI gets its own option. For the 1D case this would
look like this

.. code-block:: bash

    $ prog -r20:45 -r100:512 -r1024:1398 [OTHER OPTIONS]
