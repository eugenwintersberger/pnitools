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

class mcaops_min_test(unittest.TestCase):
    command = "../../src/mcaops/mcaops"
    base    = "/:NXentry/:NXinstrument/:NXdetector"
    total_ref = numpy.loadtxt("total_min.dat",dtype="int32")
    roi1_ref = numpy.loadtxt("roi1_min.dat",dtype="int32")
    roi2_ref = numpy.loadtxt("roi2_min.dat",dtype="int32")
    size = total_ref.size

    def result_to_ndarray(self,result):
        result = numpy.fromstring(result,dtype="float64",count=self.size,sep='\n')
        return result.round().astype("int32")

    def get_total_result(self):
        result =  check_output([self.command,"--base="+self.base,
                      "-mdata","min","fiodata.nxs"])
        return result

    def get_roi1_result(self):
        return check_output([self.command,"--roi=5:501","--base="+self.base,
                      "-mdata","min","fiodata.nxs"])

    def get_roi2_result(self):
        return check_output([self.command,"--roi=1024:2013","--base="+self.base,
                      "-mdata","min","fiodata.nxs"])

    def test_total_sum(self):
        result = self.result_to_ndarray(self.get_total_result())
        for (ref,res) in zip(self.total_ref.flat,result.flat):
            self.assertEqual(ref,res)

    def test_roi1_sum(self):
        result = self.result_to_ndarray(self.get_roi1_result())

        for (ref,res) in zip(self.roi1_ref.flat,result.flat):
            self.assertEqual(ref,res)


    def test_roi2_sum(self):
        result = self.result_to_ndarray(self.get_roi2_result())

        for (ref,res) in zip(self.roi2_ref.flat,result.flat):
            self.assertEqual(ref,res)

class mcaops_min_test_fio(mcaops_min_test):
    
    file_format = "../data/fio/scan_mca_%05i.fio"
    files1 = file_format+":1:11"
    files2 = file_format+":42:96"

    def get_total_result(self):
        result =  check_output([self.command,"min",
                                self.files1,self.files2,
                               ])
        return result

    def get_roi1_result(self):
        return check_output([self.command,"--roi=5:501","min",
                             self.files1,self.files2])

    def get_roi2_result(self):
        return check_output([self.command,"--roi=1024:2013", "min",
                             self.files1,self.files2])


class mcaops_min_test_stdio(mcaops_min_test):

    input_files = (
    "../data/fio/scan_mca_00001.fio","../data/fio/scan_mca_00002.fio",
    "../data/fio/scan_mca_00003.fio","../data/fio/scan_mca_00004.fio",
    "../data/fio/scan_mca_00005.fio","../data/fio/scan_mca_00006.fio",
    "../data/fio/scan_mca_00007.fio","../data/fio/scan_mca_00008.fio",
    "../data/fio/scan_mca_00009.fio","../data/fio/scan_mca_00010.fio",
    "../data/fio/scan_mca_00042.fio","../data/fio/scan_mca_00043.fio",
    "../data/fio/scan_mca_00044.fio","../data/fio/scan_mca_00045.fio",
    "../data/fio/scan_mca_00046.fio","../data/fio/scan_mca_00047.fio",
    "../data/fio/scan_mca_00048.fio","../data/fio/scan_mca_00049.fio",
    "../data/fio/scan_mca_00050.fio","../data/fio/scan_mca_00051.fio",
    "../data/fio/scan_mca_00052.fio","../data/fio/scan_mca_00053.fio",
    "../data/fio/scan_mca_00054.fio","../data/fio/scan_mca_00055.fio",
    "../data/fio/scan_mca_00056.fio","../data/fio/scan_mca_00057.fio",
    "../data/fio/scan_mca_00058.fio","../data/fio/scan_mca_00059.fio",
    "../data/fio/scan_mca_00060.fio","../data/fio/scan_mca_00061.fio",
    "../data/fio/scan_mca_00062.fio","../data/fio/scan_mca_00063.fio",
    "../data/fio/scan_mca_00064.fio","../data/fio/scan_mca_00065.fio",
    "../data/fio/scan_mca_00066.fio","../data/fio/scan_mca_00067.fio",
    "../data/fio/scan_mca_00068.fio","../data/fio/scan_mca_00069.fio",
    "../data/fio/scan_mca_00070.fio","../data/fio/scan_mca_00071.fio",
    "../data/fio/scan_mca_00072.fio","../data/fio/scan_mca_00073.fio",
    "../data/fio/scan_mca_00074.fio","../data/fio/scan_mca_00075.fio",
    "../data/fio/scan_mca_00076.fio","../data/fio/scan_mca_00077.fio",
    "../data/fio/scan_mca_00078.fio","../data/fio/scan_mca_00079.fio",
    "../data/fio/scan_mca_00080.fio","../data/fio/scan_mca_00081.fio",
    "../data/fio/scan_mca_00082.fio","../data/fio/scan_mca_00083.fio",
    "../data/fio/scan_mca_00084.fio","../data/fio/scan_mca_00085.fio",
    "../data/fio/scan_mca_00086.fio","../data/fio/scan_mca_00087.fio",
    "../data/fio/scan_mca_00088.fio","../data/fio/scan_mca_00089.fio",
    "../data/fio/scan_mca_00090.fio","../data/fio/scan_mca_00091.fio",
    "../data/fio/scan_mca_00092.fio","../data/fio/scan_mca_00093.fio",
    "../data/fio/scan_mca_00094.fio","../data/fio/scan_mca_00095.fio")

    def get_total_result(self):
        
        result = ""
        for input_file in self.input_files:
            tail = Popen(["tail","-n2048",input_file],stdout=PIPE)
            result += check_output([self.command,"min"],stdin=tail.stdout)

        return result
    
    def get_roi1_result(self):
        result = ""
        for input_file in self.input_files:
            tail = Popen(["tail","-n2048",input_file],stdout=PIPE)
            result += check_output([self.command,"--roi=5:501","min"],
                                    stdin=tail.stdout)

        return result

    def get_roi2_result(self):
        result = ""
        for input_file in self.input_files:
            tail = Popen(["tail","-n2048",input_file],stdout=PIPE)
            result += check_output([self.command,"--roi=1024:2013","min"],
                                    stdin=tail.stdout)

        return result



#---------------------------run the program if necessary----------------------
if __name__ == "__main__":
    unittest.main()
