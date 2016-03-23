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

total_rebin = []
roi1_rebin = []
roi2_rebin = []
total_rebin_norm = []
roi1_rebin_norm = []
roi2_rebin_norm = []

channels = numpy.arange(5,2048+5,dtype="float64")

def rebin(data,binsize,normalize=False):
    rebined_data = []
    for s in range(0,data.size,binsize):
        
        norm = 1

        if s+binsize<=data.size:
            d = data[s:s+binsize]
        else:
            d = data[s:data.size]
           
        if normalize: norm = d.size

        rebined_data.append(d.sum()/norm)

    return numpy.array(rebined_data,dtype="float64")

channels = rebin(channels,125,True)
numpy.savetxt("rebin_channels.dat",channels,fmt="%.16f")



for i in range(mca.shape[0]):
    data = mca[i,:]
    roi1_data = data[roi1[0]:roi1[1]]
    roi2_data = data[roi2[0]:roi2[1]]

    total_sum.append(data.sum())
    total_min.append(data.min())
    total_max.append(data.max())
    total_argmax.append(numpy.argmax(data))
    total_argmin.append(numpy.argmin(data))
    total_average.append(data.astype("float64").sum()/data.size)

    roi1_sum.append(roi1_data.sum())
    roi1_min.append(roi1_data.min())
    roi1_max.append(roi1_data.max())
    roi1_argmax.append(numpy.argmax(roi1_data))
    roi1_argmin.append(numpy.argmin(roi1_data))
    roi1_average.append(roi1_data.astype("float64").sum()/roi1_data.size)

    roi2_sum.append(roi2_data.sum())
    roi2_min.append(roi2_data.min())
    roi2_max.append(roi2_data.max())
    roi2_argmax.append(numpy.argmax(roi2_data))
    roi2_argmin.append(numpy.argmin(roi2_data))
    roi2_average.append(roi2_data.astype("float64").sum()/roi2_data.size)

    total_rebin.append(rebin(data.astype("float64"),125))
    roi1_rebin.append(rebin(roi1_data.astype("float64"),125))
    roi2_rebin.append(rebin(roi2_data.astype("float64"),125))

    total_rebin_norm.append(rebin(data.astype("float64"),125,True))
    roi1_rebin_norm.append(rebin(roi1_data.astype("float64"),125,True))
    roi2_rebin_norm.append(rebin(roi2_data.astype("float64"),125,True))




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

numpy.savetxt("total_rebin.dat",numpy.array(total_rebin),fmt="%.16f")
numpy.savetxt("roi1_rebin.dat",numpy.array(roi1_rebin),fmt="%.16f")
numpy.savetxt("roi2_rebin.dat",numpy.array(roi2_rebin),fmt="%.16f")

numpy.savetxt("total_rebin_norm.dat",numpy.array(total_rebin_norm),fmt="%.16f")
numpy.savetxt("roi1_rebin_norm.dat",numpy.array(roi1_rebin_norm),fmt="%.16f")
numpy.savetxt("roi2_rebin_norm.dat",numpy.array(roi2_rebin_norm),fmt="%.16f")
