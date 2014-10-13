.\" detinfo
.\" Contact Eugen Wintersberger <eugen.wintersberger@desy.de> for typos and corrections
.TH detinfo 1 "29.01.2013" "" "User commands"
.SH NAME
detinfo - prints detector information from data files

.SH SYNOPSIS
.B detinfo [OPTIONS] FILE [FILE ...]

.SH DESCRIPTION
\fBdetinfo\fR prints information about detector data stored in files. 
.br
Currently \fBdetinfo\fR supports the following file formats:
.RS 3 
.P
 - CBF - the DECTRIS flavor used for Pilatus detectors
.br
 - TIF - used by many other detectors to hold data
.br
 - Nexus using HDF5 as a storage backend.
.RE
.P
The following information is provided by \fBdetinfo\fR
.RS 3
.P 
- the path to the data (file path and/or Nexus object path)
.br
- the number of frames stored in the file or NXdetector group
.br
- the number of elements along each dimension of a single detector frame
.br
- the data type used for each pixel
.br
- the detector type
.RE
.P
Possible detector types are \fBpoint\fR, \fBlinear\fR, and \fBarea\fR.
.P 
For TIF and CBF files \fBdetinfo\fR assumes that all the data in a file belongs
.br
to a single detector. However, Nexus files are slightly different as they can 
.br
store data from several detectors in a file. In this case, the information
.br
listed above is shown for each instance of NXdetector (the group type used to 
.br
store data from an individual detector) available in the file.
.P
A typical application of \fBdetinfo\fR would be to gather all the information
.br
required to merge data from single TIF or CBF files into a Nexus file. 
.P
As with all programs from the \fBpni-tools\fR-package input files can be
.br
specified as individual files and/or as a file template with a numeric range. 
.br
For details see the info page for pni-tools how to do this.

.SH OPTIONS
The programm takes the following options:
.TP
\fB\-h\fR,\fB\-\-help\fR
print short program help
.TP
\fB\-f\fR,\fB\-\-format\fR
select the output format. Currently this option can take the following values
.RS
.P
\fBsimple\fR   - producing simple output 
.br
\fBcsv\fR      - format output as CSV table 
.br
\fBkeyvalue\fR - format output as key-value pairs
.br
\fBxml\fR      - format output as XML
.RE

.SH EXIT CODE
0 in the case of success, 1 otherwise

.SH AUTHOR
Written bei Eugen Wintersberger <eugen.wintersberger@desy.de>

.SH COPYRIGHT
Copyright 2013 Eugen Wintersberger License GLPLv2+: GNU GPL version 2 or later
.br
<http://gnu.org/license/gpl.html>.  This is free software: you are free to
.br
change and redistribute it. There is no WARRENTY, to the extent permitted by
.br
law.

.SH SEE ALSO
.IP \fBpni-tools\fR 




