.\" detinfo
.\" Contact Eugen Wintersberger <eugen.wintersberger@desy.de> for typos and corrections
.TH xml2nx 1 "Jun 17,2013" "" "User commands"
.SH NAME
xml2nx - convert XML to Nexus files 

.SH SYNOPSIS
.B xml2nx [OPTIONS] FILE [FILE ...]

.SH DESCRIPTION
\fBxml2nx\fR converts XML files holding NXDL content to Nexus files. This
program can be used to create fields and groups in a Nexus file on the basis of
an NXDL file. It thus might be useful for systems using the shell as their
operating environment. 
.P 
The NXDL file does not necessarily need to contain the full file structure. It
is even possible to add only a particular base class or component to the file. 
This is particularly useful if one wants to play with different components.

.SH OPTIONS
The programm takes the following options:
.TP
\fB\-h\fR,\fB\-\-help\fR
print short program help
.TP
\fB\-p\fR,\fB\-\-parent\fR
The parent node under which the content described by the NXDL file should be
attached. 
.TP
\fB\-o\fR,\fB\-\-overwrite\fR
Overwrite the file. With this option set an already existing file of same name
will be overwritten.

.SH EXIT CODE
0 in the case of success, 1 otherwise

.SH AUTHOR
Written bei Eugen Wintersberger <eugen.wintersberger@desy.de>

.SH COPYRIGHT
Copyright 2013 Eugen Wintersberger License GLPLv2+: GNU GPL version 2 or later
<http://gnu.org/license/gpl.html>.  This is free software: you are free to
change and redistribute it. There is no WARRENTY, to the extent permitted by
law.

.SH SEE ALSO
.IP \fBpni-tools\fR 



