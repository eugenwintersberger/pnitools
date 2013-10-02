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
#  Created on: Oct 02, 2013
#      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
#
from subprocess import check_output
from subprocess import STDOUT
from subprocess import call
import unittest
import os
import pni.io.nx.h5 as nx

class nxls_test(unittest.TestCase):
    input_file = "data/nexus/nxls_test.nxs"

    def setUp(self):
        pass

    def tearDown(self):
        pass

    def test_return(self):
        #there are currently three situations where the program should fail
        # 1.) no input file is given
        # 2.) the input file does not exist
        # 3.) the input file is not a Nexus/HDF5 file

        #should give a useage message and return 1
        cmd = ['nxls'] 
        result = int(call(cmd))
        self.assertEqual(result,1)

        #should return 1 as the group does not exist in the file
        cmd = ['nxls','bla.nxs']
        result = int(call(cmd))
        self.assertEqual(result,1)

        #should return 1 as the file is not a nexus file
        cmd = ['nxls','xml2nx_test.py']
        result = int(call(cmd))
        self.assertEqual(result,1)

    def test_simple_list(self):
        output = ['entry:NXentry']
        #just produce a simple output list
        cmd = ['nxls',self.input_file]
        result = check_output(cmd)
        self.assertEqual(result.strip(),'/entry:NXentry')

        #check more lines
        output = ['/entry:NXentry/instrument:NXinstrument',
                '/entry:NXentry/sample:NXsample','/entry:NXentry/control:NXmonitor',
                '/entry:NXentry/data:NXdata',
                '/entry:NXentry/title','/entry:NXentry/experiment_description',
                '/entry:NXentry/start_time','/entry:NXentry/end_time',
                '/entry:NXentry/program_name']
        result = check_output(['nxls',self.input_file+'://:NXentry'])
        result = result.split('\n')
        result.remove('')
        self.assertEqual(len(result),len(output))

        for r in result:
            self.assertEqual(output.count(r.strip()),1)
        
    def test_recursive_list(self):
        pass

    def test_attribute_list(self):
        pass



if __name__ == "__main__":
    unittest.main()
