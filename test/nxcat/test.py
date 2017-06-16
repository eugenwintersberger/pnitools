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
from subprocess import check_output
from subprocess import STDOUT
from subprocess import call
import unittest
import os
import os.path
import numpy

here = os.path.dirname(os.path.abspath(__file__))
bin_path = os.path.join(here,"..","..","bin")
data_path = os.path.join(here,"..","data","nexus")

class nxcat_test(unittest.TestCase):
    input_file = os.path.join(data_path,"nxls_test.nxs")
    nxcat = os.path.join(bin_path,"nxcat")

    def setUp(self):
        #need to delete the file before we can start a new run
        pass

    def tearDown(self):
        pass

    #check the return value of the program
    def test_return(self):

        #should give a useage message and return 1
        cmd = [self.nxcat]
        self.assertEqual(int(call(cmd)),1)

        #should return 1 as the file does not exist
        cmd = [self.nxcat,'test.nxs']
        self.assertEqual(int(call(cmd)),1)

        #shoule return 1 as the file is not a Nexus file
        cmd = [self.nxcat,'test.py']
        self.assertEqual(int(call(cmd)),1)

        #should return 1 as the target object is not a field or attribute
        cmd = [self.nxcat,self.input_file+'://:NXentry']
        self.assertEqual(int(call(cmd)),1)

        #this should finally work
        cmd = [self.nxcat,self.input_file+'://:NXentry/program_name']
        self.assertEqual(int(call(cmd)),0)


    #test reading string data
    def test_read_string_field(self):
        cmd = [self.nxcat,self.input_file+'://:NXentry/program_name']
        result = check_output(cmd)
        result = result.strip()
        self.assertEqual(result,"xml2nx")


    #read a string attribute
    def test_read_string_attribute(self):
        cmd = [self.nxcat,self.input_file+'://:NXentry/program_name@version']
        result = check_output(cmd)
        result = result.strip()
        self.assertEqual(result,"0.1.0")

    #append read a float field
    def test_read_float_field(self):
        path = self.input_file
        path += '://:NXentry/:NXinstrument/:NXdetector/x_pixel_size'
        cmd = [self.nxcat,path]
        result = check_output(cmd)
        print "Print the result ", result
        self.assertAlmostEqual(float(result),12.45,2)

    #read scalar field data array
    def test_read_float_array_field(self):
        #read reference data
        data = numpy.loadtxt('../data/fio/tstfile_00012.fio',skiprows=32)
        pos  = data[:,0]
        det1 = data[:,1]
        path = '../data/nexus/tstfile_00012.h5'
        path += '://:NXentry/:NXinstrument/channel_1/polar_angle'
        result = check_output([self.nxcat,path])
        pa_nx = numpy.fromstring(result,sep='\n')

        #check for size
        self.assertEqual(pa_nx.size,pos.size)

        #check data
        for x,y in zip(pa_nx,pos):
            self.assertAlmostEqual(x,y,4)




if __name__ == "__main__":
    unittest.main()
