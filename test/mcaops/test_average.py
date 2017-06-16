#!/usr/bin/env python

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

from __future__ import print_function
from subprocess import STDOUT
from subprocess import call
from subprocess import PIPE
from subprocess import Popen
from subprocess import check_output
import numpy
import unittest
import os
import pni.io.nx.h5 as nx
import common

digit_places = 7

class mcaops_average_test(unittest.TestCase):
    total_sum_ref = numpy.loadtxt("total_average.dat",dtype="float64")
    roi1_sum_ref = numpy.loadtxt("roi1_average.dat",dtype="float64")
    roi2_sum_ref = numpy.loadtxt("roi2_average.dat",dtype="float64")
    size = total_sum_ref.size


    def get_total_result(self):
        result =  check_output([common.command,common.base_opt,
                      common.mca_opt,"average","fiodata.nxs"])
        return result

    def get_roi1_result(self):
        return check_output([common.command,common.roi1_opt,common.base_opt,
                      common.mca_opt,"average","fiodata.nxs"])

    def get_roi2_result(self):
        return check_output([common.command,common.roi2_opt,common.base_opt,
                      common.mca_opt,"average","fiodata.nxs"])

    def test_total_sum(self):
        result = common.result_to_ndarray(self.get_total_result(),
                                          self.size,dtype="float64")
        for (ref,res) in zip(self.total_sum_ref.flat,result.flat):
            self.assertAlmostEqual(ref,res,places=digit_places)

    def test_roi1_sum(self):
        result = common.result_to_ndarray(self.get_roi1_result(),
                                          self.size,dtype="float64")

        for (ref,res) in zip(self.roi1_sum_ref.flat,result.flat):
            self.assertAlmostEqual(ref,res,places=digit_places)


    def test_roi2_sum(self):
        result = common.result_to_ndarray(self.get_roi2_result(),
                                          self.size,dtype="float64")

        for (ref,res) in zip(self.roi2_sum_ref.flat,result.flat):
            self.assertAlmostEqual(ref,res,places=digit_places)

class mcaops_average_test_fio(mcaops_average_test):

    def get_total_result(self):
        result =  check_output([common.command,"average",
                                common.files1,common.files2,
                               ])
        return result

    def get_roi1_result(self):
        return check_output([common.command,common.roi1_opt,"average",
                             common.files1,common.files2])

    def get_roi2_result(self):
        return check_output([common.command,common.roi2_opt, "average",
                             common.files1,common.files2])


class mcaops_average_test_stdio(mcaops_average_test):

    def get_total_result(self):

        result = ""
        for input_file in common.input_files:
            tail = Popen(["tail","-n2048",input_file],stdout=PIPE)
            result += check_output([common.command,"average"],stdin=tail.stdout)

        return result

    def get_roi1_result(self):
        result = ""
        for input_file in common.input_files:
            tail = Popen(["tail","-n2048",input_file],stdout=PIPE)
            result += check_output([common.command,common.roi1_opt,"average"],
                                    stdin=tail.stdout)

        return result

    def get_roi2_result(self):
        result = ""
        for input_file in common.input_files:
            tail = Popen(["tail","-n2048",input_file],stdout=PIPE)
            result += check_output([common.command,common.roi2_opt,"average"],
                                    stdin=tail.stdout)

        return result



#---------------------------run the program if necessary----------------------
if __name__ == "__main__":
    unittest.main()
