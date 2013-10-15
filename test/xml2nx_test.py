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
import sys


class xml2nx_test(unittest.TestCase):

    out_file = "xml2nx_test.nxs"

    def tearDown(self):
        try:
            os.remove(self.out_file)
        except:
            pass

    def __check_basic(self):
        #this should have created a Nexus file - need to check the content
        f = nx.open_file(self.out_file)
        self.assertEqual(f['entry'].attr('NX_class').value,'NXentry')
        self.assertEqual(f['entry/title'].read().strip(),"Default entry")
        self.assertEqual(f['entry/experiment_description'].read().strip(),
        "This is a plain template which contains"
        " the standard field and groups")
        self.assertEqual(f['entry/start_time'].read().strip(),'123')
        self.assertEqual(f['entry/end_time'].read().strip(),'124')
        self.assertEqual(f['entry/program_name'].read().strip(),'xml2nx')
        self.assertEqual(f['entry/program_name'].attr('version').value.strip(),
                '0.1.0');
        self.assertEqual(f['entry/program_name'].attr('configuration').value.strip(),
                'none');
        self.assertEqual(f['entry/instrument/name'].read().strip(),
                'High resolution beamline')
        self.assertEqual(f['entry/instrument/name'].attr('short_name').value.strip(),
                'P08')
        self.assertEqual(f['entry/instrument/source/name'].read().strip(),
                'Positron-Elektron Tandem Ring Anlage III')
        self.assertEqual(f['entry/instrument/source/name'].attr('short_name').value.strip(),
                "PETRA III")
        self.assertEqual(f['entry/instrument/source/type'].read().strip(),
                "Synchrotron X-ray Source")
        self.assertEqual(f['entry/instrument/source/probe'].read().strip(),
                'x-ray')

        #for the other groups we just can check the existence
        self.assertEqual(f['entry/sample'].attr('NX_class').value.strip(),'NXsample')
        self.assertEqual(f['entry/control'].attr('NX_class').value.strip(),'NXmonitor')
        self.assertEqual(f['entry/data'].attr('NX_class').value.strip(),'NXdata')
        f.close()

    def __check_detector(self):
        rpath = 'entry/instrument/detector/'
        
        f = nx.open_file(self.out_file)

        self.assertAlmostEqual(f[rpath+'x_pixel_size'].read(),12.45,places=5)
        self.assertAlmostEqual(f[rpath+'y_pixel_size'].read(),13.45,places=5)

        data = f[rpath+'data']
        print data.shape
        print data.dtype
        self.assertEqual(len(data.shape),2)
        self.assertEqual(data.shape[0],0)
        self.assertEqual(data.shape[1],2048)
        self.assertEqual(data.dtype,'uint32')
        
        self.assertEqual(f[rpath+'layout'].read().strip(),'linear')
        self.assertEqual(f[rpath+'description'].read().strip(),'PSD')
        self.assertAlmostEqual(f[rpath+'distance'].read(),0.8,places=5)


        f.close()

    #check the return values
    def test_return(self):
        #ok - too less arguments - this must fail
        cmd = ['xml2nx']
        result = int(call(cmd))
        self.assertEqual(result,1)

        #this should everything is there
        cmd = ['xml2nx','-p'+self.out_file,'basic.xml']
        result = int(call(cmd))
        self.assertEqual(result,0)

        #the file exists - this should not work
        result = int(call(cmd))
        self.assertEqual(result,1)

        #this however yes
        cmd = ['xml2nx','-o','-p'+self.out_file,'basic.xml']
        result = int(call(cmd))
        self.assertEqual(result,0)

        #if we do not specify an output file - abort
        cmd = ['xml2nx','basic.xml']
        result = int(call(cmd))
        self.assertEqual(result,1)

    #check file creation
    def test_create_file(self):
        cmd = ['xml2nx','-p'+self.out_file,'basic.xml']
        result = int(call(cmd))
        self.assertEqual(result,0)

        self.__check_basic() 

    def test_create_stdin(self):
        pass

    #check appending content
    def test_append_file(self):
        cmd = ['xml2nx','-p'+self.out_file,'basic.xml']
        result = int(call(cmd))
        self.assertEqual(result,0)
        cmd = ['xml2nx',
               '-p'+self.out_file+'://:NXentry/:NXinstrument/',
               'detector.xml']
        result = int(call(cmd))
        self.assertEqual(result,0)
        print check_output(['h5ls','-v','-r',self.out_file])

        self.__check_basic()
        self.__check_detector()


    def test_append_stdin(self):
        pass


if __name__ == "__main__":
    unittest.main(argv=sys.argv)
