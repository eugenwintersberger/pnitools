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

class mcaops_scale(unittest.TestCase):
    command = [common.command]
    scale_opts = ["scale","-x3.45","-d8.34"]
    center_value = 3.45
    delta = 8.34

    maxpos = numpy.loadtxt("total_argmax.dat",dtype="float64")
    maxpos = maxpos.round().astype("int32")

    #-------------------------------------------------------------------------
    def get_channels(self,index):
        
        tail = Popen(["tail","-n2048",common.input_files[index]],stdout=PIPE)
        result = check_output(self.command + ["--auto-index-offset=5"]+ 
                              self.rebin_opt, stdin=tail.stdout)
        
        result = result.replace("\n"," ")
        result = numpy.fromstring(result,sep=" ",dtype="float64")
        result = result.reshape((result.size/2,2))

        return result

    def test_auto_center(self):
        pass


    def test_manual_center(self):
        pass

