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
from __future__ import print_function
from subprocess import check_output
from subprocess import STDOUT
from subprocess import call
import unittest
import pni.io.nx.h5 as nexus

nexus_simple_output ="""
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_1:NXdetector/data  type = point  pixel type = UINT64  frames = 2001 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_10:NXdetector/data  type = point  pixel type = UINT64  frames = 2001 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_2:NXdetector/data  type = point  pixel type = UINT64  frames = 2001 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_3:NXdetector/data  type = point  pixel type = UINT64  frames = 2001 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_4:NXdetector/data  type = point  pixel type = UINT64  frames = 2001 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_5:NXdetector/data  type = point  pixel type = UINT64  frames = 2001 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_6:NXdetector/data  type = point  pixel type = UINT64  frames = 2001 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_7:NXdetector/data  type = point  pixel type = UINT64  frames = 2001 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_8:NXdetector/data  type = point  pixel type = UINT64  frames = 2001 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_9:NXdetector/data  type = point  pixel type = UINT64  frames = 2001 
"""

nexus_kv_output="""
source           = ../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_1:NXdetector/data
type             = point
pixel type       = UINT64
number of frames = 2001
frame shape      = 

source           = ../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_10:NXdetector/data
type             = point
pixel type       = UINT64
number of frames = 2001
frame shape      = 

source           = ../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_2:NXdetector/data
type             = point
pixel type       = UINT64
number of frames = 2001
frame shape      = 

source           = ../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_3:NXdetector/data
type             = point
pixel type       = UINT64
number of frames = 2001
frame shape      = 

source           = ../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_4:NXdetector/data
type             = point
pixel type       = UINT64
number of frames = 2001
frame shape      = 

source           = ../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_5:NXdetector/data
type             = point
pixel type       = UINT64
number of frames = 2001
frame shape      = 

source           = ../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_6:NXdetector/data
type             = point
pixel type       = UINT64
number of frames = 2001
frame shape      = 

source           = ../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_7:NXdetector/data
type             = point
pixel type       = UINT64
number of frames = 2001
frame shape      = 

source           = ../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_8:NXdetector/data
type             = point
pixel type       = UINT64
number of frames = 2001
frame shape      = 

source           = ../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_9:NXdetector/data
type             = point
pixel type       = UINT64
number of frames = 2001
frame shape      = 
"""

nexus_csv_output="""
source ; type ; pixel type ; number of frames ; frame shape
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_1:NXdetector/data ; point ; UINT64 ; 2001 ; 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_10:NXdetector/data ; point ; UINT64 ; 2001 ; 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_2:NXdetector/data ; point ; UINT64 ; 2001 ; 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_3:NXdetector/data ; point ; UINT64 ; 2001 ; 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_4:NXdetector/data ; point ; UINT64 ; 2001 ; 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_5:NXdetector/data ; point ; UINT64 ; 2001 ; 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_6:NXdetector/data ; point ; UINT64 ; 2001 ; 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_7:NXdetector/data ; point ; UINT64 ; 2001 ; 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_8:NXdetector/data ; point ; UINT64 ; 2001 ; 
../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_9:NXdetector/data ; point ; UINT64 ; 2001 ;
"""

nexus_xml_output="""
<?xml version="1.0"?>
<detinfo>
	<detector>
		<source>../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_1:NXdetector/data</source>
		<type>point</type>
		<pixeltype>UINT64</pixel>
		<frames>2001</frames>
		<frameshape></frameshape>
	</detector>
	<detector>
		<source>../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_10:NXdetector/data</source>
		<type>point</type>
		<pixeltype>UINT64</pixel>
		<frames>2001</frames>
		<frameshape></frameshape>
	</detector>
	<detector>
		<source>../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_2:NXdetector/data</source>
		<type>point</type>
		<pixeltype>UINT64</pixel>
		<frames>2001</frames>
		<frameshape></frameshape>
	</detector>
	<detector>
		<source>../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_3:NXdetector/data</source>
		<type>point</type>
		<pixeltype>UINT64</pixel>
		<frames>2001</frames>
		<frameshape></frameshape>
	</detector>
	<detector>
		<source>../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_4:NXdetector/data</source>
		<type>point</type>
		<pixeltype>UINT64</pixel>
		<frames>2001</frames>
		<frameshape></frameshape>
	</detector>
	<detector>
		<source>../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_5:NXdetector/data</source>
		<type>point</type>
		<pixeltype>UINT64</pixel>
		<frames>2001</frames>
		<frameshape></frameshape>
	</detector>
	<detector>
		<source>../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_6:NXdetector/data</source>
		<type>point</type>
		<pixeltype>UINT64</pixel>
		<frames>2001</frames>
		<frameshape></frameshape>
	</detector>
	<detector>
		<source>../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_7:NXdetector/data</source>
		<type>point</type>
		<pixeltype>UINT64</pixel>
		<frames>2001</frames>
		<frameshape></frameshape>
	</detector>
	<detector>
		<source>../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_8:NXdetector/data</source>
		<type>point</type>
		<pixeltype>UINT64</pixel>
		<frames>2001</frames>
		<frameshape></frameshape>
	</detector>
	<detector>
		<source>../data/nexus/tstfile_00012.h5://entry:NXentry/instrument:NXinstrument/channel_9:NXdetector/data</source>
		<type>point</type>
		<pixeltype>UINT64</pixel>
		<frames>2001</frames>
		<frameshape></frameshape>
	</detector>
</detinfo>
"""

tif_simple_output="""
../data/tif/detector_009.tif  type = area  pixel type = UINT32  frames = 1 frame shape = (2300,2300)
../data/tif/detector_010.tif  type = area  pixel type = UINT32  frames = 1 frame shape = (2300,2300)
../data/tif/detector_011.tif  type = area  pixel type = UINT32  frames = 1 frame shape = (2300,2300)
../data/tif/detector_012.tif  type = area  pixel type = UINT32  frames = 1 frame shape = (2300,2300)
../data/tif/detector_013.tif  type = area  pixel type = UINT32  frames = 1 frame shape = (2300,2300)
../data/tif/detector_014.tif  type = area  pixel type = UINT32  frames = 1 frame shape = (2300,2300)
../data/tif/detector_015.tif  type = area  pixel type = UINT32  frames = 1 frame shape = (2300,2300)
"""

tif_kv_output="""
source           = ../data/tif/detector_009.tif
type             = area
pixel type       = UINT32
number of frames = 1
frame shape      = (2300,2300)

source           = ../data/tif/detector_010.tif
type             = area
pixel type       = UINT32
number of frames = 1
frame shape      = (2300,2300)

source           = ../data/tif/detector_011.tif
type             = area
pixel type       = UINT32
number of frames = 1
frame shape      = (2300,2300)

source           = ../data/tif/detector_012.tif
type             = area
pixel type       = UINT32
number of frames = 1
frame shape      = (2300,2300)

source           = ../data/tif/detector_013.tif
type             = area
pixel type       = UINT32
number of frames = 1
frame shape      = (2300,2300)

source           = ../data/tif/detector_014.tif
type             = area
pixel type       = UINT32
number of frames = 1
frame shape      = (2300,2300)

source           = ../data/tif/detector_015.tif
type             = area
pixel type       = UINT32
number of frames = 1
frame shape      = (2300,2300)
"""

tif_csv_output="""
source ; type ; pixel type ; number of frames ; frame shape
../data/tif/detector_009.tif ; area ; UINT32 ; 1 ; (2300,2300)
../data/tif/detector_010.tif ; area ; UINT32 ; 1 ; (2300,2300)
../data/tif/detector_011.tif ; area ; UINT32 ; 1 ; (2300,2300)
../data/tif/detector_012.tif ; area ; UINT32 ; 1 ; (2300,2300)
../data/tif/detector_013.tif ; area ; UINT32 ; 1 ; (2300,2300)
../data/tif/detector_014.tif ; area ; UINT32 ; 1 ; (2300,2300)
../data/tif/detector_015.tif ; area ; UINT32 ; 1 ; (2300,2300)
"""

tif_xml_output="""
<?xml version="1.0"?>
<detinfo>
	<detector>
		<source>../data/tif/detector_009.tif</source>
		<type>area</type>
		<pixeltype>UINT32</pixel>
		<frames>1</frames>
		<frameshape>(2300,2300)</frameshape>
	</detector>
	<detector>
		<source>../data/tif/detector_010.tif</source>
		<type>area</type>
		<pixeltype>UINT32</pixel>
		<frames>1</frames>
		<frameshape>(2300,2300)</frameshape>
	</detector>
	<detector>
		<source>../data/tif/detector_011.tif</source>
		<type>area</type>
		<pixeltype>UINT32</pixel>
		<frames>1</frames>
		<frameshape>(2300,2300)</frameshape>
	</detector>
	<detector>
		<source>../data/tif/detector_012.tif</source>
		<type>area</type>
		<pixeltype>UINT32</pixel>
		<frames>1</frames>
		<frameshape>(2300,2300)</frameshape>
	</detector>
	<detector>
		<source>../data/tif/detector_013.tif</source>
		<type>area</type>
		<pixeltype>UINT32</pixel>
		<frames>1</frames>
		<frameshape>(2300,2300)</frameshape>
	</detector>
	<detector>
		<source>../data/tif/detector_014.tif</source>
		<type>area</type>
		<pixeltype>UINT32</pixel>
		<frames>1</frames>
		<frameshape>(2300,2300)</frameshape>
	</detector>
	<detector>
		<source>../data/tif/detector_015.tif</source>
		<type>area</type>
		<pixeltype>UINT32</pixel>
		<frames>1</frames>
		<frameshape>(2300,2300)</frameshape>
	</detector>
</detinfo>
"""

cbf_simple_output="""
../data/cbf/LAOS3_05461.cbf  type = area  pixel type = INT32  frames = 1 frame shape = (195,487)
"""

cbf_kv_output="""
source           = ../data/cbf/LAOS3_05461.cbf
type             = area
pixel type       = INT32
number of frames = 1
frame shape      = (195,487)
"""

cbf_csv_output="""
source ; type ; pixel type ; number of frames ; frame shape
../data/cbf/LAOS3_05461.cbf ; area ; INT32 ; 1 ; (195,487)
"""

cbf_xml_output="""
<?xml version="1.0"?>
<detinfo>
        <detector>
                <source>../data/cbf/LAOS3_05461.cbf</source>
                <type>area</type>
                <pixeltype>INT32</pixel>
                <frames>1</frames>
                <frameshape>(195,487)</frameshape>
        </detector>
</detinfo>
"""

dead_link_file ="""
<group name="entry" type="NXentry">
    <group name="instrument" type="NXinstrument">
        <group name="detector" type="NXdetector">
            <link name="data" target="eiger.nxs://entry/instrument/detector/data"/>
            <field name="layout" type="string">area</field>
        </group>
    </group>
</group>
"""

class detinfo_test(unittest.TestCase):

    tif_file = '../data/tif/detector_009.tif'
    cbf_file = '../data/cbf/LAOS3_05461.cbf'
    program = '../../src/detinfo/detinfo'

    def _get_cmd(self,options=[],args=[]):
        cmd = [self.program]
        cmd.extend(options)
        cmd.extend(args)
        
        return cmd

    def _call(self,options=[],args=[]):
        return call(self._get_cmd(options=options,args=args))

    def _check_output(self,options=[],args=[]):
        return check_output(self._get_cmd(options=options,args=args))

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
        result = int(self._call(args=['../data/tif/detector_%03i.tif:9:16']))
        self.assertEqual(result,0)

        #last files do not exist
        result = int(self._call(args=['../data/tif/detector_%03i.fio:1:5']))
        self.assertEqual(result,1)

        #check for single nexus file
        result = int(self._call(args=["../data/nexus/tstfile_00012.h5"]))
        self.assertEqual(result,0)
      
    #-------------------------------------------------------------------------
    def test_simple(self):
        print("test simple output ...")
        result = self._check_output(options=["-fsimple"],
                                    args = [self.cbf_file])

        self.assertEqual(result.strip(),cbf_simple_output.strip())
        
        result = self._check_output(options=["-fsimple"],
                                    args = ["../data/nexus/tstfile_00012.h5"])
        print(result)
        print(nexus_simple_output)
        self.assertEqual(result.strip(),nexus_simple_output.strip())        
        
        result = self._check_output(options=["-fsimple"],
                                    args = ["../data/tif/detector_%03i.tif:9:16"])
        self.assertEqual(result.strip(),tif_simple_output.strip())

    #-------------------------------------------------------------------------
    def test_kv(self):
        result = self._check_output(options=["-fkeyvalue"],
                                    args = [self.cbf_file])

        self.assertEqual(result.strip(),cbf_kv_output.strip())
        
        result = self._check_output(options=["-fkeyvalue"],
                                    args = ["../data/nexus/tstfile_00012.h5"])
        self.assertEqual(result.strip(),nexus_kv_output.strip())        

        result = self._check_output(options=["-fkeyvalue"],
                                    args = ["../data/tif/detector_%03i.tif:9:16"])
        self.assertEqual(result.strip(),tif_kv_output.strip())

    #-------------------------------------------------------------------------
    def test_csv(self):
        result = self._check_output(options=["-fcsv"],
                                    args = ["../data/nexus/tstfile_00012.h5"])
        self.assertEqual(result.strip(),nexus_csv_output.strip())        

        result = self._check_output(options=["-fcsv"],
                                    args = ["../data/tif/detector_%03i.tif:9:16"])
        self.assertEqual(result.strip(),tif_csv_output.strip())
        
        result = self._check_output(options=["-fcsv"],
                                    args = [self.cbf_file])

        self.assertEqual(result.strip(),cbf_csv_output.strip())

    #-------------------------------------------------------------------------
    def test_xml(self):
        replace = "        ";
        result = self._check_output(options=["-fxml"],
                                    args = [self.cbf_file])
    
        result = result.strip().replace("\t",replace)
        self.assertEqual(result,cbf_xml_output.strip())
        
        result = self._check_output(options=["-fxml"],
                                    args = ["../data/nexus/tstfile_00012.h5"])
        self.assertEqual(result.strip(),nexus_xml_output.strip())        

        result = self._check_output(options=["-fxml"],
                                    args = ["../data/tif/detector_%03i.tif:9:16"])
        self.assertEqual(result.strip(),tif_xml_output.strip())


    def test_unresolvable_link(self):
        f = nexus.create_file("unresolvable_link.nxs",overwrite=True)
        r = f.root()
        nexus.xml_to_nexus(dead_link_file,r,lambda x: True)
        r.close()
        f.close()

        result = self._check_output(args=["unresolvable_link.nxs"])
        print(result)




         
if __name__ == "__main__":
    unittest.main()
