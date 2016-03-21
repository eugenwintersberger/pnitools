#!/usr/bin/env python3

import numpy
import pni.io.nx.h5 as nexus

f = nexus.open_file("fiodata.nxs")
r = f.root()
mca = nexus.get_object(r,"/:NXentry/:NXinstrument/:NXdetector/data")[...]

roi1 = (5,501)
roi2 = (1024,2013)

total_sum = []
roi1_sum  = []
roi2_sum  = []

total_min = []
roi1_min  = []
roi2_min  = []

total_max = []
roi1_max  = []
roi2_max  = []

for i in range(mca.shape[0]):
    data = mca[i,:]
    total_sum.append(data.sum())
    total_min.append(data.min())
    total_max.append(data.max())
    roi1_sum.append(data[roi1[0]:roi1[1]].sum())
    roi2_sum.append(data[roi2[0]:roi2[1]].sum())
    roi1_min.append(data[roi1[0]:roi1[1]].min())
    roi2_min.append(data[roi2[0]:roi2[1]].min())
    roi1_max.append(data[roi1[0]:roi1[1]].max())
    roi2_max.append(data[roi2[0]:roi2[1]].max())


numpy.savetxt("total_sum.dat",numpy.array(total_sum),fmt="%i")
numpy.savetxt("roi1_sum.dat",numpy.array(roi1_sum),fmt="%i")
numpy.savetxt("roi2_sum.dat",numpy.array(roi2_sum),fmt="%i")

numpy.savetxt("total_min.dat",numpy.array(total_min),fmt="%i")
numpy.savetxt("roi1_min.dat",numpy.array(roi1_min),fmt="%i")
numpy.savetxt("roi2_min.dat",numpy.array(roi2_min),fmt="%i")

numpy.savetxt("total_max.dat",numpy.array(total_max),fmt="%i")
numpy.savetxt("roi1_max.dat",numpy.array(roi1_max),fmt="%i")
numpy.savetxt("roi2_max.dat",numpy.array(roi2_max),fmt="%i")
