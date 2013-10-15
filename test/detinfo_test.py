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

class detinfo_test(unittest.TestCase):

    tif_file = 'data/tif/detector_009.tif'
    cbf_file = 'data/cbf/LAOS3_05461.cbf'
    program = 'detinfo'

    def _get_cmd(self,options=[],args=[]):
        cmd = [self.program]
        cmd.extend(options)
        cmd.extend(args)
        
        return cmd

    def _call(self,options=[],args=[]):
        return call(self._get_cmd(options=options,args=args))

    def _check_output(self,options=[],args=[]):
        return check_output(self._get_cmd(options=options,args=args))

    def _check_size(self,filename,option,size):
        result = int(self._check_output(options=[option],args=[filename]))
        self.assertEqual(result,size)

    def test_return(self):
        # possible problems that might occur
        # -> a file does not exist
        # -> a file exists but is not supported

        #file exists but type is not supported q
        result = int(self._call(args=['detinfo_test.py']))
        self.assertEqual(result,1)

        #file does not exist
        result = int(self._call(args=['bla.txt'])); 
        self.assertEqual(result,1)

        #should be ok
        result = int(self._call(args=['data/tif/detector_%03i.tif:9:16']))
        self.assertEqual(result,0)

        #last files do not exist
        result = int(self._call(args=['data/tif/detector_%03i.fio:1:5']))
        self.assertEqual(result,1)

    def test_size(self):
        #test the total size of images
        self._check_size(self.tif_file,"-n",2300*2300)
        self._check_size(self.tif_file,"--ntot",2300*2300)
        self._check_size(self.cbf_file,"-n",195*487)
        self._check_size(self.cbf_file,"--ntot",195*487)

    def test_x_resolution(self):
        self._check_size(self.tif_file,"-x",2300)
        self._check_size(self.tif_file,"--nx",2300)
        self._check_size(self.cbf_file,"-x",195)
        self._check_size(self.cbf_file,"--nx",195)

    def test_y_resolution(self):
        self._check_size(self.tif_file,"-y",2300)
        self._check_size(self.tif_file,"--ny",2300)
        self._check_size(self.cbf_file,"-y",487)
        self._check_size(self.cbf_file,"--ny",487)

    def test_type(self):
        result = self._check_output(options=['-d'],args=[self.tif_file])
        self.assertEqual(result.strip(),'UINT32')

        result = self._check_output(options=['-d'],args=[self.cbf_file])
        self.assertEqual(result.strip(),"INT32")

    def test_list(self):
        #check the list output
        arg = 'data/tif/detector_%03i.tif:9:16'
        result = self._check_output(options=['-l'],args=[arg])
        # we have to remove the last element which holds only a blank
        result = result.split('\n')[:-1]
        self.assertEqual(len(result),7)

         
if __name__ == "__main__":
    unittest.main()
