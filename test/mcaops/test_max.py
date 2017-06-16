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
import common

class mcaops_max_test(unittest.TestCase):
    total_ref = numpy.loadtxt("total_max.dat",dtype="int32")
    roi1_ref = numpy.loadtxt("roi1_max.dat",dtype="int32")
    roi2_ref = numpy.loadtxt("roi2_max.dat",dtype="int32")
    size = total_ref.size

    def get_total_result(self):
        result =  check_output([common.command,common.base_opt,
                      common.mca_opt,"max","fiodata.nxs"])
        return result

    def get_roi1_result(self):
        return check_output([common.command,common.roi1_opt,common.base_opt,
                      common.mca_opt,"max","fiodata.nxs"])

    def get_roi2_result(self):
        return check_output([common.command,common.roi2_opt,common.base_opt,
                      common.mca_opt,"max","fiodata.nxs"])

    def test_total_sum(self):
        result = common.result_to_ndarray(self.get_total_result(),self.size)
        for (ref,res) in zip(self.total_ref.flat,result.flat):
            self.assertEqual(ref,res)

    def test_roi1_sum(self):
        result = common.result_to_ndarray(self.get_roi1_result(),self.size)

        for (ref,res) in zip(self.roi1_ref.flat,result.flat):
            self.assertEqual(ref,res)


    def test_roi2_sum(self):
        result = common.result_to_ndarray(self.get_roi2_result(),self.size)

        for (ref,res) in zip(self.roi2_ref.flat,result.flat):
            self.assertEqual(ref,res)

class mcaops_max_test_fio(mcaops_max_test):

    def get_total_result(self):
        result =  check_output([common.command,"max",
                                common.files1,common.files2,
                               ])
        return result

    def get_roi1_result(self):
        return check_output([common.command,common.roi1_opt,"max",
                             common.files1,common.files2])

    def get_roi2_result(self):
        return check_output([common.command,common.roi2_opt, "max",
                             common.files1,common.files2])


class mcaops_max_test_stdio(mcaops_max_test):

    def get_total_result(self):

        result = ""
        for input_file in common.input_files:
            tail = Popen(["tail","-n2048",input_file],stdout=PIPE)
            result += check_output([common.command,"max"],stdin=tail.stdout)

        return result

    def get_roi1_result(self):
        result = ""
        for input_file in common.input_files:
            tail = Popen(["tail","-n2048",input_file],stdout=PIPE)
            result += check_output([common.command,common.roi1_opt,"max"],
                                    stdin=tail.stdout)

        return result

    def get_roi2_result(self):
        result = ""
        for input_file in common.input_files:
            tail = Popen(["tail","-n2048",input_file],stdout=PIPE)
            result += check_output([common.command,common.roi2_opt,"max"],
                                    stdin=tail.stdout)

        return result



#---------------------------run the program if necessary----------------------
if __name__ == "__main__":
    unittest.main()
