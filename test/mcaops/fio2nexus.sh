#!/usr/bin/env python3

import numpy

print("starting conversion")

input_files = (
"../data/fio/scan_mca_00001.fio", "../data/fio/scan_mca_00002.fio", 
"../data/fio/scan_mca_00003.fio", "../data/fio/scan_mca_00004.fio",
"../data/fio/scan_mca_00005.fio", "../data/fio/scan_mca_00006.fio",
"../data/fio/scan_mca_00007.fio", "../data/fio/scan_mca_00008.fio",
"../data/fio/scan_mca_00009.fio", "../data/fio/scan_mca_00010.fio",
"../data/fio/scan_mca_00042.fio", "../data/fio/scan_mca_00043.fio",
"../data/fio/scan_mca_00044.fio", "../data/fio/scan_mca_00045.fio",
"../data/fio/scan_mca_00046.fio", "../data/fio/scan_mca_00047.fio",
"../data/fio/scan_mca_00048.fio", "../data/fio/scan_mca_00049.fio",
"../data/fio/scan_mca_00050.fio", "../data/fio/scan_mca_00051.fio",
"../data/fio/scan_mca_00052.fio", "../data/fio/scan_mca_00053.fio",
"../data/fio/scan_mca_00054.fio", "../data/fio/scan_mca_00055.fio",
"../data/fio/scan_mca_00056.fio", "../data/fio/scan_mca_00057.fio",
"../data/fio/scan_mca_00058.fio", "../data/fio/scan_mca_00059.fio",
"../data/fio/scan_mca_00060.fio", "../data/fio/scan_mca_00061.fio",
"../data/fio/scan_mca_00062.fio", "../data/fio/scan_mca_00063.fio",
"../data/fio/scan_mca_00064.fio", "../data/fio/scan_mca_00065.fio",
"../data/fio/scan_mca_00066.fio", "../data/fio/scan_mca_00067.fio",
"../data/fio/scan_mca_00068.fio", "../data/fio/scan_mca_00069.fio",
"../data/fio/scan_mca_00070.fio", "../data/fio/scan_mca_00071.fio",
"../data/fio/scan_mca_00072.fio", "../data/fio/scan_mca_00073.fio",
"../data/fio/scan_mca_00074.fio", "../data/fio/scan_mca_00075.fio",
"../data/fio/scan_mca_00076.fio", "../data/fio/scan_mca_00077.fio",
"../data/fio/scan_mca_00078.fio", "../data/fio/scan_mca_00079.fio",
"../data/fio/scan_mca_00080.fio", "../data/fio/scan_mca_00081.fio",
"../data/fio/scan_mca_00082.fio", "../data/fio/scan_mca_00083.fio",
"../data/fio/scan_mca_00084.fio", "../data/fio/scan_mca_00085.fio",
"../data/fio/scan_mca_00086.fio", "../data/fio/scan_mca_00087.fio",
"../data/fio/scan_mca_00088.fio", "../data/fio/scan_mca_00089.fio",
"../data/fio/scan_mca_00090.fio", "../data/fio/scan_mca_00091.fio",
"../data/fio/scan_mca_00092.fio", "../data/fio/scan_mca_00093.fio",
"../data/fio/scan_mca_00094.fio", "../data/fio/scan_mca_00095.fio",)

for fio_file in input_files:
    data = numpy.loadtxt(fio_file,skiprows=115)
    print(fio_file)
    print(data.size)

