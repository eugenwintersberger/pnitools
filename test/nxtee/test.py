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
#  Created on: Jun 4, 2015
#      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
#

from __future__ import print_function
from subprocess import check_output
from subprocess import STDOUT
from subprocess import call
from subprocess import PIPE
from subprocess import Popen
import unittest
import os
import os.path
import pni.io.nx.h5 as nx

append_data = "1 2 3 4 5\n 6 7 8 9 10\n 11 12 13 14 15"
replace_data = "10 20 30 40 50\n 60 70 80 90 100\n 110 120 130 140 150"

here = os.path.dirname(os.path.abspath(__file__))
bin_path = os.path.join(here,"..","..","bin")

class nxtee_test(unittest.TestCase):
    filename = "nxtee_test.nxs"
    instrument = filename+"://:NXentry/:NXinstrument"
    nxtee = os.path.join(bin_path,"nxtee")
    xml2nx = os.path.join(bin_path,"xml2nx")
    def setUp(self):
        call([self.xml2nx,'-o',"-p"+self.filename+"://","mca.xml"])

    def tearDown(self):
        pass

    def test_return(self):
        #-------------fails - cannot do append on an attribute-------
        echo = Popen(["echo","counts"],stdout=PIPE)
        result = call([self.nxtee,self.instrument+"/mca2/data@units"],
                      stdin=echo.stdout)
        self.assertEqual(int(result),1)

    def test_append_field(self):
        echo = Popen(["echo",append_data],stdout=PIPE)
        result = call([self.nxtee,self.instrument+"/mca/data"],
                      stdin=echo.stdout)
        print(result)

        #readback data
        f = nx.open_file(self.filename)
        d = f.root()["entry"]["instrument"]["mca"]["data"]
        print(d.shape)
        self.assertEqual(d.shape[0],3)
        self.assertEqual(d.shape[1],5)
        data = d[...]
        f.close()
        for f,r in zip(data.flat,range(1,16)):
            self.assertEqual(f,r)

    def test_replace_field(self):
        echo = Popen(["echo",replace_data],stdout=PIPE)
        result = call([self.nxtee,'-r',self.instrument+"/mca2/data"],
                      stdin=echo.stdout)

        #readback data
        f = nx.open_file(self.filename)
        d = f.root()["entry"]["instrument"]["mca2"]["data"]
        data = d[...]
        f.close()
        for f,r in zip(data.flat,range(10,160,10)):
            self.assertEqual(f,r)

    def test_replace_attribute(self):
        echo = Popen(["echo","counts"],stdout=PIPE)
        result = call([self.nxtee,'-r',self.instrument+"/mca2/data@units"],
                      stdin=echo.stdout)

        f = nx.open_file(self.filename)
        d = f.root()["entry"]["instrument"]["mca2"]["data"]
        self.assertEqual(d.attributes['units'].read(),"counts")
        f.close()


#---------------------------run the program if necessary----------------------
if __name__ == "__main__":
    unittest.main()
