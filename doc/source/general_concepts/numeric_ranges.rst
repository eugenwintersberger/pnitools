
Describing numeric ranges
=========================

In many cases the user is required to specify a range of integers. 
All programs in the **pnitools** distribution use a coherent syntax for this
purpose which is similar to how ranges are specified in Python. 
In its most general form the syntax reads

Numeric range
    <start>:<stop>[:<stride>]

where the last field (*stride*) is optional. The fields have the following
meaning

========  ===========================================
field     description
========  ===========================================
*start*   the first number in the range
*stop*    the last number (not included in the range)
*stride*  stride between the elements of the range
========  ===========================================

Using this the range from 1 to 100 can be given with

.. code-block:: text

    1:101 = 1,2,3,4,5,...,99,100

it is important to note that the last value is not included. To get only the
even numbers a stride of 2 can be added 

.. code-block:: text

    2:101:2 = 2,4,6,8,10,...98,100

Possible applications of numeric ranges are for instance regions of interests or
series of file names that include a number.
