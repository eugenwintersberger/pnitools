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
#  Created on: Sep 17, 2013
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

class det2nx_test(unittest.TestCase):
    image_list = "data/tif/detector_%03i.tif:9:16"
    image      = "data/tif/detector_050.tif"

    def setUp(self):
        #need to delete the file before we can start a new run
        pass

    def tearDown(self):
        #remove the temporary test file if it exists
        try:
            os.remove('det2nx1.nx')
        except:
            pass

    def test_return(self):
        print "Test program return values ..."
        #should give a useage message and return 1
        cmd = ['det2nx'] 
        result = int(call(cmd))
        self.assertEqual(result,1)

        #should return 1 as the group does not exist in the file
        cmd = ['det2nx','-gdet2nx1.nx://:NXentry',self.image_list]
        result = int(call(cmd))
        self.assertEqual(result,1)

        #input files do not exist
        cmd = ['det2nx','-gdet2nx1.nx://data','bla.dat']
        result = int(call(cmd))
        self.assertEqual(result,1)

        #input file is not supporte
        cmd = ['det2nx','-gdet2nx1.nx://data','det2nx_test.py']
        result = int(call(cmd))
        self.assertEqual(result,1)

        #this should work
        cmd = ['det2nx','-gdet2nx1.nx://data',self.image_list]
        result = int(call(cmd))
        self.assertEqual(result,0)


    #test the creation of a file and initial data import
    #take care about the fact that det2nx assumes all paths within the file to
    #exist. Only the target field will be created automatically.
    def test_create(self):
        print "test file creation ..."
        cmd = ['det2nx','-gdet2nx1.nx://data',self.image_list]
        result = int(call(cmd))
        self.assertEqual(result,0)

        #now we have to investigate the file
        f = nx.open_file('det2nx1.nx')
        d = f['data']
        self.assertEqual(d.shape[0],7)
        self.assertEqual(d.shape[1],2300)
        self.assertEqual(d.shape[2],2300)
        f.close()


    #append an image to an existing image stack
    def test_append(self):
        self.test_create()

        cmd = ['det2nx','-tdet2nx1.nx://data','data/tif/detector_050.tif']
        result = int(call(cmd))
        self.assertEqual(result,0)

        #now we have to investigate the file
        f = nx.open_file('det2nx1.nx')
        d = f['data']
        self.assertEqual(d.shape[0],8)
        self.assertEqual(d.shape[1],2300)
        self.assertEqual(d.shape[2],2300)
        f.close()

    #overwrite an existing file
    def test_overwrite(self):
        self.test_append()

        cmd = ['det2nx','--overwrite','-tdet2nx1.nx://data',
               'data/tif/detector_050.tif']
        result = int(call(cmd))
        self.assertEqual(result,0)

        #now we have to investigate the file
        f = nx.open_file('det2nx1.nx')
        d = f['data']
        self.assertEqual(d.shape[0],1)
        self.assertEqual(d.shape[1],2300)
        self.assertEqual(d.shape[2],2300)
        f.close()

if __name__ == "__main__":
    unittest.main()
