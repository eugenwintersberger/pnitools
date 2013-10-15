#
# (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
#
# This file is part of pnitools.
#
# pnitools is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# pnitools is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
#************************************************************************
#
#  Created on: Oct 15, 2013
#      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
#
import popen2

def check_output(command):
    """
    check_output(command):

    Provides a somwhat limited version of the check_output function provided by
    the subprocess package shipped with Python 2.7.

    required arguments:
    commane ............ list of command an its arguments and options

    return 
    string with the program output on standard out
    """

    out_stream,in_file = popen2.popen2(command)
    res = ""
    for line in out_stream: 
        res += line

    return res
