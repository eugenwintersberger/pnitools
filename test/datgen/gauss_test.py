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
#  Created on: Jun 24, 2015
#      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
#

from subprocess import check_output
from subprocess import STDOUT
from subprocess import call
import unittest
import os
import pni.io.nx.h5 as nx
import numpy
import os.path

here = os.path.dirname(os.path.abspath(__file__))
bin_path = os.path.join(here,"..","..","bin")

class gauss(object):
    def __init__(self,a,s,m):
        self._amp = a
        self._sigma = s
        self._mu = m
        self._p = a/s/numpy.sqrt(2.*numpy.pi)

    def __call__(self,x):
        a = -0.5*((x-self._mu)/self._sigma)**2
        return self._p*numpy.exp(a)


class gauss_test(unittest.TestCase):

    cmd = [os.path.join(bin_path,'datgen'),'-b100','-e200','--show-grid','-s4','gauss']

    def setUp(self):
        #need to delete the file before we can start a new run
        pass

    def tearDown(self):
        pass

    def test_return(self):
        pass

    def test_sigma_fail(self):
        result = int(call(self.cmd+['-s1x']))
        self.assertEqual(result,1)

    def test_mu_fail(self):
        result = int(call(self.cmd+['-m1x']))
        self.assertEqual(result,1)

    def test_amplitude_fail(self):
        result = int(call(self.cmd+['-a1u']))
        self.assertEqual(result,1)

    def test_calc1(self):
        print "HELLO I FUCK YOU ALL!"
        cmd = self.cmd+['-a5','-s2','-m0.5']
        result = check_output(cmd)
        data = numpy.fromstring(result,sep=" ").reshape(4,2)
        xdata = data[:,0]
        ydata = data[:,1]
        f = gauss(5.,2.,0.5)

        for (x,y) in zip(xdata,ydata):
            self.assertAlmostEqual(y,f(x),8)


if __name__ == "__main__":
    unittest.main()
