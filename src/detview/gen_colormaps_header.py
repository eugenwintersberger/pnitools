from matplotlib import pyplot 

header = open("ColorMaps.hpp","w")
header.write("#ifndef __COLORMAPS_HPP__\n")
header.write("#define __COLORMAPS_HPP__\n\n")

def generate_map(cmap):
    ostr = "double rgba[%i][4] = {" %cmap.N

    for i in range(cmap.N):
        color = cmap(i)
        ostr += "{%f," %(color[0])
        ostr += "%f," %(color[1])
        ostr += "%f," %(color[2])
        ostr += "%f},\n" %(color[3])

    ostr = ostr[:-1] +"};"

    return ostr


header.write(generate_map(pyplot.cm.jet))
header.write("\n#endif")



        
