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
import numpy
import os.path

here = os.path.dirname(os.path.abspath(__file__))
bin_path = os.path.join(here,"..","..","bin")


class datgen_linear_test(unittest.TestCase):

    cmd = [os.path.join(bin_path,'datgen'),'-b100','-e200','--show-grid','-s4','linear']

    def setUp(self):
        #need to delete the file before we can start a new run
        pass

    def tearDown(self):
        pass

    def test_return(self):
        pass

    def test_slope_wrong(self):
        result = int(call(self.cmd+['-s1x','-o23']))
        self.assertEqual(result,1)

    def test_offset_wrong(self):
        result = int(call(self.cmd+['-s1','-o2ssx']))
        self.assertEqual(result,1);

    def test_calc1(self):
        cmd = self.cmd+['-s2','-o-4.']
        result = check_output(cmd)
        data = numpy.fromstring(result,sep=" ").reshape(4,2)
        xdata = data[:,0]
        ydata = data[:,1]

        for (x,y) in zip(xdata,ydata):
            self.assertAlmostEqual(y,2.*x-4.0,8)




if __name__ == "__main__":
    unittest.main()
