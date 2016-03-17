
.. _numeric_ranges-label:

Describing numeric ranges
=========================

In many cases the user is required to specify a range of integers in a command
line option or argument. 
All programs in the **pnitools** distribution use a coherent syntax for this
purpose which is similar to how ranges are specified in Python
[#slice_footnote]_. 
In `EBNF`_ a numeric range is defined as 

.. productionlist:: numeric_range_rule
    numeric_range: start, ":" , stop, [":" stride ]
    start: index
    stop: index
    stride: index 
    index: { digit } 
    digit: "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"


===============  ===========================================
field            description
===============  ===========================================
:token:`start`   the first number in the range
:token:`stop`    the last number (not included in the range)
:token:`stride`  stride between the elements of the range
===============  ===========================================

The :token:`stride` token is optional. Though this looks rather complicated the
application of numeric ranges is rather simple and straight forward.
Using this the range from 1 to 100 can be given with

.. code-block:: text

    1:101 = 1,2,3,4,5,...,99,100

it is important to note that the last value is not included. To get only the
even numbers a :token:`lstride` of 2 can be added 

.. code-block:: text

    2:101:2 = 2,4,6,8,10,...98,100

Possible applications of numeric ranges are for instance regions of interests or
series of file names that include a number.

Rational: why omitting the last index?
--------------------------------------

The reade may ask why we have choosen to omit the last index from a range. The
reason for this is that we follow the standard C and Python counting
convention and want to keep this convention consistent over all programs even
it seems a bit awkward in some cases (for instance ROIs). 

We think that a consistent behavior is much more convenient than having
different index schemes for every application or use case. The user has to
learn and keep in mind only one convention and can rely on it in every
situation where a numeric range is required.

.. [#slice_footnote] Numeric ranges used for indexing lists ore numeric arrays
                     are called ``slices`` in Python.
.. _EBNF: https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_Form
