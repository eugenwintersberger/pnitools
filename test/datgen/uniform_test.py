#!/usr/bin/env python

#
# (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
#  Created on: Jun 22, 2015
#      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
#

from subprocess import check_output
from subprocess import STDOUT
from subprocess import call
import unittest
import os
import pni.io.nx.h5 as nx

class datgen_uniform_test(unittest.TestCase):

    cmd = ['../../src/datgen/datgen','-b100','-e200','-s2','uniform']

    def setUp(self):
        #need to delete the file before we can start a new run
        pass

    def tearDown(self):
        pass

    def test_return(self):
        pass

    def test_ok(self):
        result = int(call(self.cmd+['-l1.2','-u4.5']))
        self.assertEqual(result,0)

    def test_lower_wrong(self):
        result = int(call(self.cmd+['-l1.2x','-u4.5']))
        self.assertEqual(result,1)
    
    def test_upper_wrong(self):
        result = int(call(self.cmd+['-l1.2','-u4.5x']))
        self.assertEqual(result,1)

    def test_upper_larger_lower(self):
        result = int(call(self.cmd+['-l1.2','-u0.2']))
        self.assertEqual(result,1)



if __name__ == "__main__":
    unittest.main()
