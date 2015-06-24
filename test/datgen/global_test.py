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
import numpy

class datgen_global_test(unittest.TestCase):

    def setUp(self):
        pass

    def tearDown(self):
        pass

    def test_return(self):
        pass

    def test_noargs_noopts(self):
        cmd = ['datgen']
        result = int(call(cmd))
        self.assertEqual(result,1)

    def test_nofunctor(self):
        cmd = ['datgen','-b100','-e200','-s2']
        self.assertEqual(int(call(cmd)),1);

    def test_wrong_functor(self):
        cmd = ['datgen','-b100','-e200','-s2','uni']
        self.assertEqual(int(call(cmd)),1);
    
    def test_missing_grid_endpoint(self):
        result = int(call(['datgen','-b100','-s2','uniform']))
        self.assertEqual(result,1)
    
    def test_missing_grid_startpoint(self):
        result = int(call(['datgen','-e100','-s2','uniform']))
        self.assertEqual(result,1)

    def test_missing_grid_steps(self):
        result = int(call(['datgen','-e100','-b2','uniform']))
        self.assertEqual(result,1)

    def test_grid_end_small_start(self):
        result = int(call(['datgen','-b100','-e2','-s1','uniform']))
        self.assertEqual(result,1)

    def test_grid(self):
        cmd = ['datgen','-b100','-e200','-s10','--show-grid','uniform']
        result = check_output(cmd)
        data = numpy.fromstring(result,sep=" ").reshape(10,2)
        xdata = data[:,0]
        delta = (200.-100.)/(10.-1.)
        x = 100
        for xcli in xdata:
            self.assertAlmostEqual(xcli,x,8)
            x += delta




if __name__ == "__main__":
    unittest.main()
