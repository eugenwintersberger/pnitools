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
#  Created on: Mar 18, 2016
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

class mcaops_test_sum(unittest.TestCase):
    command = "../../src/mcaops/mcaops"
    base    = "/:NXentry/:NXinstrument/:NXdetector"
    total_sum_ref = numpy.loadtxt("total_sum.dat",dtype="int32")
    roi1_sum_ref = numpy.loadtxt("roi1_sum.dat",dtype="int32")
    roi2_sum_ref = numpy.loadtxt("roi2_sum.dat",dtype="int32")
    size = total_sum_ref.size

    def result_to_ndarray(self,result):
        result = numpy.fromstring(result,dtype="float64",count=self.size,sep='\n')
        return result.round().astype("int32")

    def get_total_result(self):
        return check_output([self.command,"--base="+self.base,
                      "-mdata","sum","fiodata.nxs"])

    def get_roi1_result(self):
        return check_output([self.command,"--roi=5:501","--base="+self.base,
                      "-mdata","sum","fiodata.nxs"])

    def get_roi2_result(self):
        return check_output([self.command,"--roi=1024:2013","--base="+self.base,
                      "-mdata","sum","fiodata.nxs"])

    def test_total_sum(self):
        result = self.result_to_ndarray(self.get_total_result())

        for (ref,res) in zip(self.total_sum_ref.flat,result.flat):
            self.assertEqual(ref,res)

    def test_roi1_sum(self):
        result = self.result_to_ndarray(self.get_roi1_result())

        for (ref,res) in zip(self.roi1_sum_ref.flat,result.flat):
            self.assertEqual(ref,res)


    def test_roi2_sum(self):
        result = self.result_to_ndarray(self.get_roi2_result())

        for (ref,res) in zip(self.roi2_sum_ref.flat,result.flat):
            self.assertEqual(ref,res)

class mcaops_test_sum_fio(mcaops_test_sum):
    
    file_format = "../data/fio/scan_mca_%05i.fio"
    files = file_format+":1:11 "+file_format+":42:95"

    def get_total_result(self):
        print(self.files)
        print(self.command)
        result =  check_output([self.command,"sum",self.files])
        print(result)
        return result

    def get_roi1_result(self):
        return check_output([self.command,"--roi=5:501","sum",self.files])

    def get_roi2_result(self):
        return check_output([self.command,"--roi=1024:2013", "sum",self.files])


class mcaops_test_sum_stdio(mcaops_test_sum):
    pass

#---------------------------run the program if necessary----------------------
if __name__ == "__main__":
    unittest.main()
