#
# (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
#  Created on: Mar 18, 2016
#      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
#

import numpy
import os.path
import sys


roi1_opt = "--roi=5:501"
roi2_opt = "--roi=1024:2013"
base_opt = "--base=/:NXentry/:NXinstrument/:NXdetector"
mca_opt  = "-mdata"

here = os.path.dirname(os.path.abspath(__file__))
bin_path = os.path.join(here,"..","..","bin")
data_path = os.path.join(here,"..","data")
fio_path = os.path.join(data_path,"fio")
command = os.path.join(bin_path,"mcaops")

file_format = os.path.join(fio_path,"scan_mca_%05i.fio")
files1 = file_format+":1:11"
files2 = file_format+":42:96"

input_files = (
    os.path.join(fio_path,"scan_mca_00001.fio"),
    os.path.join(fio_path,"scan_mca_00002.fio"),
    os.path.join(fio_path,"scan_mca_00003.fio"),
    os.path.join(fio_path,"scan_mca_00004.fio"),
    os.path.join(fio_path,"scan_mca_00005.fio"),
    os.path.join(fio_path,"scan_mca_00006.fio"),
    os.path.join(fio_path,"scan_mca_00007.fio"),
    os.path.join(fio_path,"scan_mca_00008.fio"),
    os.path.join(fio_path,"scan_mca_00009.fio"),
    os.path.join(fio_path,"scan_mca_00010.fio"),
    os.path.join(fio_path,"scan_mca_00042.fio"),
    os.path.join(fio_path,"scan_mca_00043.fio"),
    os.path.join(fio_path,"scan_mca_00044.fio"),
    os.path.join(fio_path,"scan_mca_00045.fio"),
    os.path.join(fio_path,"scan_mca_00046.fio"),
    os.path.join(fio_path,"scan_mca_00047.fio"),
    os.path.join(fio_path,"scan_mca_00048.fio"),
    os.path.join(fio_path,"scan_mca_00049.fio"),
    os.path.join(fio_path,"scan_mca_00050.fio"),
    os.path.join(fio_path,"scan_mca_00051.fio"),
    os.path.join(fio_path,"scan_mca_00052.fio"),
    os.path.join(fio_path,"scan_mca_00053.fio"),
    os.path.join(fio_path,"scan_mca_00054.fio"),
    os.path.join(fio_path,"scan_mca_00055.fio"),
    os.path.join(fio_path,"scan_mca_00056.fio"),
    os.path.join(fio_path,"scan_mca_00057.fio"),
    os.path.join(fio_path,"scan_mca_00058.fio"),
    os.path.join(fio_path,"scan_mca_00059.fio"),
    os.path.join(fio_path,"scan_mca_00060.fio"),
    os.path.join(fio_path,"scan_mca_00061.fio"),
    os.path.join(fio_path,"scan_mca_00062.fio"),
    os.path.join(fio_path,"scan_mca_00063.fio"),
    os.path.join(fio_path,"scan_mca_00064.fio"),
    os.path.join(fio_path,"scan_mca_00065.fio"),
    os.path.join(fio_path,"scan_mca_00066.fio"),
    os.path.join(fio_path,"scan_mca_00067.fio"),
    os.path.join(fio_path,"scan_mca_00068.fio"),
    os.path.join(fio_path,"scan_mca_00069.fio"),
    os.path.join(fio_path,"scan_mca_00070.fio"),
    os.path.join(fio_path,"scan_mca_00071.fio"),
    os.path.join(fio_path,"scan_mca_00072.fio"),
    os.path.join(fio_path,"scan_mca_00073.fio"),
    os.path.join(fio_path,"scan_mca_00074.fio"),
    os.path.join(fio_path,"scan_mca_00075.fio"),
    os.path.join(fio_path,"scan_mca_00076.fio"),
    os.path.join(fio_path,"scan_mca_00077.fio"),
    os.path.join(fio_path,"scan_mca_00078.fio"),
    os.path.join(fio_path,"scan_mca_00079.fio"),
    os.path.join(fio_path,"scan_mca_00080.fio"),
    os.path.join(fio_path,"scan_mca_00081.fio"),
    os.path.join(fio_path,"scan_mca_00082.fio"),
    os.path.join(fio_path,"scan_mca_00083.fio"),
    os.path.join(fio_path,"scan_mca_00084.fio"),
    os.path.join(fio_path,"scan_mca_00085.fio"),
    os.path.join(fio_path,"scan_mca_00086.fio"),
    os.path.join(fio_path,"scan_mca_00087.fio"),
    os.path.join(fio_path,"scan_mca_00088.fio"),
    os.path.join(fio_path,"scan_mca_00089.fio"),
    os.path.join(fio_path,"scan_mca_00090.fio"),
    os.path.join(fio_path,"scan_mca_00091.fio"),
    os.path.join(fio_path,"scan_mca_00092.fio"),
    os.path.join(fio_path,"scan_mca_00093.fio"),
    os.path.join(fio_path,"scan_mca_00094.fio"),
    os.path.join(fio_path,"scan_mca_00095.fio"))


def result_to_ndarray(result,size,dtype="int32",sep='\n'):

    if isinstance(result,bytes):
        result = str(result,'utf-8')

    result = numpy.fromstring(result,dtype="float64",count=size,sep=sep)

    if dtype=="int32":
        return result.round().astype(dtype)
    else:
        return result
