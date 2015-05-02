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
        r = f.root()
        e = r["entry"]
        self.assertEqual(e.attributes['NX_class'].value,'NXentry')
        self.assertEqual(e['title'].read()[0].strip(),"Default entry")
        self.assertEqual(e['experiment_description'].read()[0].strip(),
        "This is a plain template which contains"
        " the standard field and groups")
        self.assertEqual(e['start_time'].read()[0].strip(),'123')
        self.assertEqual(e['end_time'].read()[0].strip(),'124')
        self.assertEqual(e['program_name'].read()[0].strip(),'xml2nx')
        self.assertEqual(e['program_name'].\
                attributes['version'].value[0].strip(),'0.1.0');
        self.assertEqual(e['program_name'].\
                attributes['configuration'].value[0].strip(),'none');
        self.assertEqual(e['instrument']['name'].read()[0].strip(),
                'High resolution beamline')
        self.assertEqual(e['instrument']['name'].\
                attributes['short_name'].value[0].strip(),'P08')
        self.assertEqual(e['instrument']['source']['name'].read()[0].strip(),
                'Positron-Elektron Tandem Ring Anlage III')
        self.assertEqual(e['instrument']['source']['name']\
                .attributes['short_name'].value[0].strip(),"PETRA III")
        self.assertEqual(e['instrument']['source']['type'].read()[0].strip(),
                "Synchrotron X-ray Source")
        self.assertEqual(e['instrument']['source']['probe'].read()[0].strip(),
                'x-ray')

        #for the other groups we just can check the existence
        self.assertEqual(e['sample'].attributes['NX_class'].value[0].strip(),'NXsample')
        self.assertEqual(e['control'].attributes['NX_class'].value[0].strip(),'NXmonitor')
        self.assertEqual(e['data'].attributes['NX_class'].value[0].strip(),'NXdata')
        f.close()

    def __check_detector(self):
        rpath = 'entry/instrument/detector/'
        
        f = nx.open_file(self.out_file)
        r = f.root()
        d = r['entry']['instrument']['detector']

        self.assertAlmostEqual(d['x_pixel_size'].read(),12.45,places=5)
        self.assertAlmostEqual(d['y_pixel_size'].read(),13.45,places=5)

        data = d['data']
        print data.shape
        print data.dtype
        self.assertEqual(len(data.shape),2)
        self.assertEqual(data.shape[0],0)
        self.assertEqual(data.shape[1],2048)
        self.assertEqual(data.dtype,'uint32')
        
        self.assertEqual(d['layout'].read()[0].strip(),'linear')
        self.assertEqual(d['description'].read()[0].strip(),'PSD')
        self.assertAlmostEqual(d['distance'].read(),0.8,places=5)


        f.close()

    #check the return values
    def test_return(self):
        #ok - too less arguments - this must fail
        cmd = ['xml2nx']
        result = int(call(cmd))
        self.assertEqual(result,1)

        #this should everything is there
        cmd = ['xml2nx','-p'+self.out_file+"://",'basic.xml']
        result = int(call(cmd))
        self.assertEqual(result,0)

        #the file exists - this should not work
        result = int(call(cmd))
        self.assertEqual(result,1)

        #this however yes
        cmd = ['xml2nx','-o','-p'+self.out_file+"://",'basic.xml']
        result = int(call(cmd))
        self.assertEqual(result,0)

        #if we do not specify an output file - abort
        cmd = ['xml2nx','basic.xml']
        result = int(call(cmd))
        self.assertEqual(result,1)

    #check file creation
    def test_create_file(self):
        cmd = ['xml2nx','-p'+self.out_file+"://",'basic.xml']
        result = int(call(cmd))
        self.assertEqual(result,0)

        self.__check_basic() 

    def test_create_stdin(self):
        pass

    #check appending content
    def test_append_file(self):
        cmd = ['xml2nx','-p'+self.out_file+"://",'basic.xml']
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
