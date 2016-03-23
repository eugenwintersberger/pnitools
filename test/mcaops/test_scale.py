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
#  Created on: Mar 23, 2016
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
import pni.io.nx.h5 as nx
import common

class mcaops_scale_test(unittest.TestCase):
    command = [common.command]
    scale_opts = ["scale","-x3.45","-d8.34"]
    center_value = 3.45
    delta = 8.34

    maxpos = numpy.loadtxt("total_argmax.dat",dtype="float64")
    maxpos = maxpos.round().astype("int32")
    channels = numpy.arange(0,2048,dtype="int32")

    #-------------------------------------------------------------------------
    def get_channels(self,channels):
        
        channels = channels.replace("\n"," ")
        channels = numpy.fromstring(channels,sep=" ",dtype="float64")
        channels = channels.reshape((channels.size/2,2))

        return channels[:,0]

    def compute_reference(self,channels,center):

        return 3.45+8.34*(channels-center)

    def test_auto_center(self):

        for index in range(len(common.input_files)):
            tail = Popen(["tail","-n2048",common.input_files[index]],stdout=PIPE)
            channels = check_output(self.command + self.scale_opts, 
                                  stdin=tail.stdout)
            channels = self.get_channels(channels)

            expected = self.compute_reference(numpy.arange(0,2048),self.maxpos[index])

            for (result,ref) in zip(channels.flat,expected.flat):
                self.assertAlmostEqual(result,ref)


    def test_manual_center(self):
        
        expected = self.compute_reference(numpy.arange(0,2048),1500)
        for index in range(len(common.input_files)):
            tail = Popen(["tail","-n2048",common.input_files[index]],stdout=PIPE)
            channels = check_output(self.command + self.scale_opts + 
                                    ["--center=1500"],stdin=tail.stdout)
            channels = self.get_channels(channels)

            for (result,ref) in zip(channels.flat,expected.flat):
                self.assertAlmostEqual(result,ref)


#---------------------------run the program if necessary----------------------
if __name__ == "__main__":
    unittest.main()
