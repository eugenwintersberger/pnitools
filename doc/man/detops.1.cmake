.\" mcaops
.\" Contact Eugen Wintersberger <eugen.wintersberger@desy.de> for typos and corrections
.TH man 1 "12.10.2013" "1.0" "detops man page"
.SH NAME
 detops - apply cumulative image operations on detector files
.SH SYNOPSIS
.B detops [OPTIONS] [FILE]

.SH DESCRIPTION
\fBdetops\fR is a utility program applying certain operations on 2D detector data. 
The detector data can be read from one or several single image detector files.
.sp
The operations have typically 
All results are written to standard output. This allows several \fBmcaops\fR
commands to be chained using the pipe operator. 
.sp
The behavior of \fBmcaops\fR is controlled via the command string which is
passed as the first argument to the program (see the SYNOPSIS above).  Currently
the following commands are available:
.sp
\fBmax\fR     find the value and its position in the spectrum
.sp
\fBsum\fR     add all value in the spectrum
.sp
\fBrebin\fR   rebin the spectrum to new bin sizes
.sp
\fBscale\fR   scale the bin centers of the spectrum
.sp
\fBdump\fR    dump channel and mca data unchanged to standard out
.P 
These operations can roughly devided into two groups: accumulating and
non-accumulating operations. The former one reduces the entire MCA data to a
single number while the latter one preserves the spectrum character of the data
(though rebining maybe alters the number of bins). 

.SH OPTIONS
The  options provided and their meaning depend on the operation that should be
performed on the data. Some of of the options are global and valid for all
operations other are only defined for a particular command. 
.sp
Global options:
.TP
\fB\-h\fR, \fB\-\-help\fR
Print a usage message and exit.
.TP
\fB\-v\fR, \fB\-\-verbose\fR
Produce verbose output, printing information regarding the specified options and
objects.  All output is printed to standard error allowing you to redirect
payload data to an other program while still watching debugging output.
.TP
\fB\-q\fR, \fB\-\-quiet\fR
Suppress all unnecessary output (the counterpart of -v)
.TP 
\fB\-\-header\fR
print a header before dumping the output to standard out
.TP
\fB\-\-xolumn=[COLNAME]\fR
specify the name of the column to choose from the input to use as bin-center or
-index values. This option is only useful when used in connection with FIO
files.
.TP
\fB\-\-ycolumn=[COLNAME]\fR
specify the name of the column to use for MCA data. This option is only useful
with a FIO file. 
.P
Options for the \fBrebin\fR operation:
.TP
\fB\-b\fR,\fB\-\-binsize=[NBINS]\fR
defines the number of bins that should be collated during rebining. 
.TP 
\fB\-\-noxrebin\fR 
do not rebin the x-axis. Instead use indices for the output. 
.TP
\fB\-\-normalize\fR 
normalize the rebinned data.
.P 
Options for the  \fBscale\fR operation:
.TP
\fB\-c\fR,\fB\-\-center=[CENTER]\fR
defines the index of the center bin used for rescaling. 
.TP
\fB\-d\fR,\fB\-\-delta=[DELTA]\fR
defines the step width for the rebin operation
.TP 
\fB\-x\fR,\fB\-\-cvalue=[CENTERVALUE]\fR
the value of the center bin.
.P 
The \fBsum\fR and \fBmax\fR command have no additional options.

.SH EXIT STATUS
\fBmcaops\fR returns 0 in case of success and -1 otherwise. 

.SH EXAMPLES
Lets start with a very simple example reading data form standard input and using
the accumulating operations \fBsum\fR and \fBmax\fR. For the sake of convenience 
a data file should be created which looks like this
.IP
0 1
.IP
1 0
.IP
2 10
3 50
4 100
5 200
6 70
7 150
8 20
9 1
10 0
.P
and store the file as test.dat. Here the first column is the channel index while
the second holds the channel data. 
To compute the sum of the data stored use
.TP 
$> cat test.dat | mcaops sum 
602
.P 
where the output, 602, is the sum of values stored in the second column.
Analogously, to find the maximum use
.TP 
$> cat test.dat | mcaops max
5   200
.P 
the two  numbers are the position of the maximum and its value respectively. 
.SH AUTHOR
Written by Eugen Wintersberger.

.SH SEE ALSO

