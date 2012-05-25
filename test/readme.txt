NAME

       mcatocal - calibrate mca scans taken at P01

SYNOPSIS

       mcatocal [OPTION]... [FILE]...

DESCRIPTION

       Tool to create a two column ascii file from single column mca-fio-file taken at
       P01 / PETRAIII  Beamline.
       Reads a single one column ...mca_counter.fio file, searches for the maximmum
       intensity and creates a corresponding time counter column having the value 0
       at the location of the maximum. By default, the time counter is a signed
       integer (multiplied by a constant, if optionally set).

       Writes an output file having the same filename as inputfile, but different
       file extension '.dat' with first column containing time index and second column
       the intensity (both binned, if optionally set).

       Options are

       -c, --calibration slope (or cali constant)
	     the slope to apply to the time counter values, i.e. the delta_t
             between adjacent detector channels

       -b, --binning
	      performs a channel binning (averages)
              must be of uint type

       -v, --version
	      prints the version of the tool to stdout

       -o, --calibration offset
	      if given, this channel id set to time = 0 rather than executing
              a maximum search

       -a, --allfilespeak
	      read all mca files first (wildcard?) and use their sum/average to derive
              location of time zero point
              
              Hallo Eugen,

als Nachtrag zum Tool:

ich habe mit HC gesprochen und die '-a' option würde tatsächlich gehen,
d.h. die Lage des Maximums ist für alle MCA Frames eines scans konst.

Zudem haben die Nutzer von HC bzw. HC angefragt, ob auch mehrspaltige
fios gehen würden, d.h. in meinen Augen ein col-select option oder in
manpage slang

       -n, --numcol
         the column index to use for output in case of fio files
             containing multiple data columns, n ranbges from 0 to
             'number of columns-1', 0 is default


Gruß
André 
