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

total_argmax = []
roi1_argmax  = []
roi2_argmax  = []

total_argmin = []
roi1_argmin  = []
roi2_argmin  = []

total_average = []
roi1_average  = []
roi2_average  = []


for i in range(mca.shape[0]):
    data = mca[i,:]
    total_sum.append(data.sum())
    total_min.append(data.min())
    total_max.append(data.max())
    total_argmax.append(numpy.argmax(data))
    total_argmin.append(numpy.argmin(data))
    total_average.append(data.astype("float64").sum()/data.size)
    roi1_sum.append(data[roi1[0]:roi1[1]].sum())
    roi2_sum.append(data[roi2[0]:roi2[1]].sum())
    roi1_min.append(data[roi1[0]:roi1[1]].min())
    roi2_min.append(data[roi2[0]:roi2[1]].min())
    roi1_max.append(data[roi1[0]:roi1[1]].max())
    roi2_max.append(data[roi2[0]:roi2[1]].max())
    roi1_argmax.append(numpy.argmax(data[roi1[0]:roi1[1]]))
    roi2_argmax.append(numpy.argmax(data[roi2[0]:roi2[1]]))
    roi1_argmin.append(numpy.argmin(data[roi1[0]:roi1[1]]))
    roi2_argmin.append(numpy.argmin(data[roi2[0]:roi2[1]]))
    roi1_average.append(data.astype("float64")[roi1[0]:roi1[1]].sum()/data[roi1[0]:roi1[1]].size)
    roi2_average.append(data.astype("float64")[roi2[0]:roi2[1]].sum()/data[roi2[0]:roi2[1]].size)





numpy.savetxt("total_sum.dat",numpy.array(total_sum),fmt="%i")
numpy.savetxt("roi1_sum.dat",numpy.array(roi1_sum),fmt="%i")
numpy.savetxt("roi2_sum.dat",numpy.array(roi2_sum),fmt="%i")

numpy.savetxt("total_min.dat",numpy.array(total_min),fmt="%i")
numpy.savetxt("roi1_min.dat",numpy.array(roi1_min),fmt="%i")
numpy.savetxt("roi2_min.dat",numpy.array(roi2_min),fmt="%i")

numpy.savetxt("total_max.dat",numpy.array(total_max),fmt="%i")
numpy.savetxt("roi1_max.dat",numpy.array(roi1_max),fmt="%i")
numpy.savetxt("roi2_max.dat",numpy.array(roi2_max),fmt="%i")

numpy.savetxt("total_argmax.dat",numpy.array(total_argmax),fmt="%i")
numpy.savetxt("roi1_argmax.dat",numpy.array(roi1_argmax),fmt="%i")
numpy.savetxt("roi2_argmax.dat",numpy.array(roi2_argmax),fmt="%i")

numpy.savetxt("total_argmin.dat",numpy.array(total_argmin),fmt="%i")
numpy.savetxt("roi1_argmin.dat",numpy.array(roi1_argmin),fmt="%i")
numpy.savetxt("roi2_argmin.dat",numpy.array(roi2_argmin),fmt="%i")

numpy.savetxt("total_average.dat",numpy.array(total_average),fmt="%.16f")
numpy.savetxt("roi1_average.dat",numpy.array(roi1_average),fmt="%.16f")
numpy.savetxt("roi2_average.dat",numpy.array(roi2_average),fmt="%.16f")
