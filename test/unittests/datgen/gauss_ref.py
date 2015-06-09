import numpy

amp = 2.0
sigma=0.3
mu = 1.0

def gauss(x):
    e = numpy.exp(-0.5*((x-mu)/sigma)**2)
    return amp*e/sigma/numpy.sqrt(2*numpy.pi)

print gauss(0)
print gauss(1)
print gauss(-1)
