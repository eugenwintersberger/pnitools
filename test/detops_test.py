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
#  Created on: Nov 19, 2013
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

class detops_test(unittest.TestCase):

    def setUp(self):
        #need to delete the file before we can start a new run
        pass

    def tearDown(self):
        pass

    def test_return(self):
        pass

    #test for MAR 165 data
    def test_mar165(self):
        file1 = "data/tif/mar165_agbeh_00001.tif"
        file2 = "data/tif/mar165_agbehenate1s_00001.tif"

        #check first file
        cmd = ['detops','-csum',file1]
        result = float(check_output(cmd))
        print result
        self.assertAlmostEqual(result,63058885.,8)
        cmd = ['detops','-csum','-r50:151,100:201',file1]
        result = float(check_output(cmd))
        self.assertAlmostEqual(result,14656.,8)
        cmd = ['detops','-csum','-r50:922,100:513',file1]
        result = float(check_output(cmd))
        self.assertAlmostEqual(result,32602309,8)
        
        #check second file
        cmd = ['detops','-csum',file2]
        result = float(check_output(cmd))
        print result
        self.assertAlmostEqual(result,5167152.,8)
        cmd = ['detops','-csum','-r50:151,100:201',file2]
        result = float(check_output(cmd))
        self.assertAlmostEqual(result,179792.,8)
        cmd = ['detops','-csum','-r50:461,100:257',file2]
        result = float(check_output(cmd))
        self.assertAlmostEqual(result,2032644,8)

    def test_mar345(self):
        file1 = "data/tif/mar345_LaB6_20s.tif"

        #check first file
        cmd = ['detops','-csum',file1]
        result = float(check_output(cmd))
        print result
        self.assertAlmostEqual(result,9648020923.,8)
        cmd = ['detops','-csum','-r50:151,100:201',file1]
        result = float(check_output(cmd))
        self.assertAlmostEqual(result,0.,8)
        cmd = ['detops','-csum','-r50:2071,100:1151',file1]
        result = float(check_output(cmd))
        self.assertAlmostEqual(result,4528990412.,8)

    def test_perk(self):
        file1 = "data/tif/perk_Fe_noPM_2.5barsec-05000.raw.tif"

        #check first file
        cmd = ['detops','-csum',file1]
        result = float(check_output(cmd))
        print result
        self.assertAlmostEqual(result,20958844636.,8)
        cmd = ['detops','-csum','-r50:151,100:201',file1]
        result = float(check_output(cmd))
        self.assertAlmostEqual(result,50186602.,8)
        cmd = ['detops','-csum','-r50:1844,100:1025',file1]
        result = float(check_output(cmd))
        self.assertAlmostEqual(result,8300631866.,8)

    def test_pilatus100k(self):
        file1 = "data/cbf/Pilatus100k_sample180_00001_00001.cbf"

        #check first file
        cmd = ['detops','-csum',file1]
        result = float(check_output(cmd))
        print result
        self.assertAlmostEqual(result,38063289.,8)
        cmd = ['detops','-csum','-r50:151,100:201',file1]
        result = float(check_output(cmd))
        self.assertAlmostEqual(result,102455.,8)
        cmd = ['detops','-csum','-r50:558,100:244',file1]
        result = float(check_output(cmd))
        self.assertAlmostEqual(result,5852776.,8)

    def test_pilatus1M(self):
        file1 = "data/cbf/Pilatus1M_org_00020.cbf"

        #check first file
        cmd = ['detops','-csum',file1]
        result = float(check_output(cmd))
        print result
        self.assertAlmostEqual(result,6800180.,8)
        cmd = ['detops','-csum','-r50:151,100:201',file1]
        result = float(check_output(cmd))
        self.assertAlmostEqual(result,21500.,8)
        cmd = ['detops','-csum','-r50:939,100:491',file1]
        result = float(check_output(cmd))
        self.assertAlmostEqual(result,3434172.,8)

    def test_p2m(self):
        file1 = "data/cbf/p2M_diamond_diffraction_1_1_0001.cbf"

        #check first file
        cmd = ['detops','-csum',file1]
        result = float(check_output(cmd))
        print result
        self.assertAlmostEqual(result,40590718.,8)
        cmd = ['detops','-csum','-r50:151,100:201',file1]
        result = float(check_output(cmd))
        self.assertAlmostEqual(result,62553.,8)
        cmd = ['detops','-csum','-r50:1512,100:738',file1]
        result = float(check_output(cmd))
        self.assertAlmostEqual(result,17506333.,8)


if __name__ == "__main__":
    unittest.main()
