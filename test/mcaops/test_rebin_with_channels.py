#!/usr/bin/env python

#
# (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
#  Created on: Mar 22, 2016
#      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
#

from __future__ import print_function
from subprocess import STDOUT
from subprocess import call
from subprocess import PIPE
from subprocess import Popen
from subprocess import check_output
import numpy
import unittest
import os
import common

class mcaops_rebin_with_channels(unittest.TestCase):
    command = [common.command]
    rebin_opt = ["rebin","-b125"]

    ref = numpy.loadtxt("rebin_channels.dat")

    #-------------------------------------------------------------------------
    def get_total_result(self):

        tail = Popen(["tail","-n2048",common.input_files[0]],stdout=PIPE)
        result = check_output(self.command + ["--auto-index-offset=5"]+
                              self.rebin_opt, stdin=tail.stdout)

        result = result.replace("\n"," ")
        result = numpy.fromstring(result,sep=" ",dtype="float64")
        result = result.reshape((result.size/2,2))

        return result

    def test(self):
        result =  self.get_total_result()
        channels = result[:,0]
        mca = result[:,0]

        for (r,ref) in zip(channels.flat,self.ref.flat):
            self.assertAlmostEqual(r,ref)


#---------------------------run the program if necessary----------------------
if __name__ == "__main__":
    unittest.main()
