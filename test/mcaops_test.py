#!/usr/bin/env python

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
#  Created on: Oct 11, 2013
#      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
#
from subprocess import check_output
from subprocess import STDOUT
from subprocess import call
import unittest
import os
import pni.io.nx.h5 as nx
import numpy

input_file_list = ["data/fio/scan_mca_00001.fio","data/fio/scan_mca_00002.fio",
                   "data/fio/scan_mca_00003.fio","data/fio/scan_mca_00004.fio",
                   "data/fio/scan_mca_00005.fio","data/fio/scan_mca_00006.fio",
                   "data/fio/scan_mca_00007.fio","data/fio/scan_mca_00008.fio",
                   "data/fio/scan_mca_00009.fio","data/fio/scan_mca_00010.fio",
                   "data/fio/scan_mca_00042.fio","data/fio/scan_mca_00043.fio",
                   "data/fio/scan_mca_00044.fio","data/fio/scan_mca_00045.fio",
                   "data/fio/scan_mca_00046.fio","data/fio/scan_mca_00047.fio",
                   "data/fio/scan_mca_00048.fio","data/fio/scan_mca_00049.fio",
                   "data/fio/scan_mca_00050.fio","data/fio/scan_mca_00051.fio",
                   "data/fio/scan_mca_00052.fio","data/fio/scan_mca_00053.fio",
                   "data/fio/scan_mca_00054.fio","data/fio/scan_mca_00055.fio",
                   "data/fio/scan_mca_00056.fio","data/fio/scan_mca_00057.fio",
                   "data/fio/scan_mca_00058.fio","data/fio/scan_mca_00059.fio",
                   "data/fio/scan_mca_00060.fio","data/fio/scan_mca_00061.fio",
                   "data/fio/scan_mca_00062.fio","data/fio/scan_mca_00063.fio",
                   "data/fio/scan_mca_00064.fio","data/fio/scan_mca_00065.fio",
                   "data/fio/scan_mca_00066.fio","data/fio/scan_mca_00067.fio",
                   "data/fio/scan_mca_00068.fio","data/fio/scan_mca_00069.fio",
                   "data/fio/scan_mca_00070.fio","data/fio/scan_mca_00071.fio",
                   "data/fio/scan_mca_00072.fio","data/fio/scan_mca_00073.fio",
                   "data/fio/scan_mca_00074.fio","data/fio/scan_mca_00075.fio",
                   "data/fio/scan_mca_00076.fio","data/fio/scan_mca_00077.fio",
                   "data/fio/scan_mca_00078.fio","data/fio/scan_mca_00079.fio",
                   "data/fio/scan_mca_00080.fio","data/fio/scan_mca_00081.fio",
                   "data/fio/scan_mca_00082.fio","data/fio/scan_mca_00083.fio",
                   "data/fio/scan_mca_00084.fio","data/fio/scan_mca_00085.fio",
                   "data/fio/scan_mca_00086.fio","data/fio/scan_mca_00087.fio",
                   "data/fio/scan_mca_00088.fio","data/fio/scan_mca_00089.fio",
                   "data/fio/scan_mca_00090.fio","data/fio/scan_mca_00091.fio",
                   "data/fio/scan_mca_00092.fio","data/fio/scan_mca_00093.fio",
                   "data/fio/scan_mca_00094.fio","data/fio/scan_mca_00095.fio"]

class mcaops_test(unittest.TestCase):
    input_file = 'data/fio/scan_mca_00001.fio'

    def setUp(self):
        #need to delete the file before we can start a new run
        pass

    def tearDown(self):
        pass

    #check the return value of the program
    def test_return(self):

        #should give a useage message and return 1
        cmd = ['mcaops'] 
        self.assertEqual(int(call(cmd)),1) 

        #data file will be interpreted as command which is wrong
        cmd = ['mcaops','mcaops_test.py']
        self.assertEqual(int(call(cmd)),1)

        #pass a wrong command
        cmd = ['mcaops','blabla','mcaops_test.py']
        self.assertEqual(int(call(cmd)),1)

        #pass invalid data file
        cmd = ['mcaops','sum','mcaops_test.py']
        self.assertEqual(int(call(cmd)),1)

        #pass a valid file but an invalid command
        cmd = ['mcaops','blabla', self.input_file]
        self.assertEqual(int(call(cmd)),1)

    def test_sum(self):

        def test(fname):
            cmd = ['mcaops','sum',fname]
            result = check_output(cmd)
            result = float(result)

            #read data from file
            data = numpy.loadtxt(fname,skiprows=115)
            ref = numpy.sum(data)

            return (result,ref)

        for f in input_file_list:
            result,ref = test(f)
            self.assertAlmostEqual(result,ref,8)


    def test_max(self):
        def test(fname):
            cmd = ['mcaops','max',fname]
            result = check_output(cmd)
            pos,value = result.split("\t")
            pos = int(pos.strip())
            value = float(value.strip())
            
            data = numpy.loadtxt(fname,skiprows=115)
            ref_pos = numpy.argmax(data)
            ref_value = max(data)

            return (pos,value,ref_pos,ref_value)

        for f in input_file_list:
            pos,value,ref_pos,ref_value = test(f)
            self.assertEqual(pos,ref_pos)
            self.assertAlmostEqual(value,ref_value,8)


        
    def test_rebin(self):
        pass

    def test_scale(self):
        pass



if __name__ == "__main__":
    unittest.main()
