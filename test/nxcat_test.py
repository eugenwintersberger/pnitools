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
#  Created on: Oct 07, 2013
#      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
#
try:
    from subprocess import check_output
except:
    from check_output import check_output

from subprocess import STDOUT
from subprocess import call
import unittest
import os
import pni.io.nx.h5 as nx
import numpy

class nxcat_test(unittest.TestCase):
    input_file = "data/nexus/nxls_test.nxs"

    def setUp(self):
        #need to delete the file before we can start a new run
        pass

    def tearDown(self):
        pass

    #check the return value of the program
    def test_return(self):

        #should give a useage message and return 1
        cmd = ['nxcat'] 
        self.assertEqual(int(call(cmd)),1)
        
        #should return 1 as the file does not exist
        cmd = ['nxcat','test.nxs']
        self.assertEqual(int(call(cmd)),1)

        #shoule return 1 as the file is not a Nexus file
        cmd = ['nxcat','nxcat_test.py']
        self.assertEqual(int(call(cmd)),1)

        #should return 1 as the target object is not a field or attribute
        cmd = ['nxcat',self.input_file+'://:NXentry']
        self.assertEqual(int(call(cmd)),1)

        #this should finally work
        cmd = ['nxcat',self.input_file+'://:NXentry/program_name']
        self.assertEqual(int(call(cmd)),0)


    #test reading string data
    def test_read_string_field(self):
        cmd = ['nxcat',self.input_file+'://:NXentry/program_name']
        result = check_output(cmd)
        result = result.strip()
        self.assertEqual(result,"xml2nx")


    #read a string attribute
    def test_read_string_attribute(self):
        cmd = ['nxcat',self.input_file+'://:NXentry/program_name@version']
        result = check_output(cmd)
        result = result.strip()
        self.assertEqual(result,"0.1.0")

    #append read a float field
    def test_read_float_field(self):
        path = self.input_file
        path += '://:NXentry/:NXinstrument/:NXdetector/x_pixel_size'
        cmd = ['nxcat',path]
        result = check_output(cmd)
        self.assertAlmostEqual(float(result),12.45,1.e-4)

    #read scalar field data array
    def test_read_float_array_field(self):
        #read reference data
        data = numpy.loadtxt('data/fio/tstfile_00012.fio',skiprows=32)
        pos  = data[:,0]
        det1 = data[:,1]
        path = 'data/nexus/tstfile_00012.h5'
        path += '://:NXentry/:NXinstrument/channel_1/polar_angle'
        result = check_output(['nxcat',path])
        pa_nx = numpy.fromstring(result,sep='\n')

        #check for size
        self.assertEqual(pa_nx.size,pos.size)

        #check data
        for x,y in zip(pa_nx,pos):
            self.assertAlmostEqual(x,y,7)
        



if __name__ == "__main__":
    unittest.main()
