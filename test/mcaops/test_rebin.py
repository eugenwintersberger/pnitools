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

class mcaops_rebin_test(unittest.TestCase):
    total_ref = numpy.loadtxt("total_rebin.dat",dtype="float64")
    roi1_ref = numpy.loadtxt("roi1_rebin.dat",dtype="float64")
    roi2_ref = numpy.loadtxt("roi2_rebin.dat",dtype="float64")
    total_norm_ref = numpy.loadtxt("total_rebin_norm.dat",dtype="float64")
    roi1_norm_ref = numpy.loadtxt("roi1_rebin_norm.dat",dtype="float64")
    roi2_norm_ref = numpy.loadtxt("roi2_rebin_norm.dat",dtype="float64")

    command = [common.command,"--no-channel-output","--channel-sep=' '"]
    nxopts  = [common.base_opt,common.mca_opt]
    rebin_opt = ["rebin","-b125"]

    #-------------------------------------------------------------------------
    def check_result(self,result,expected):
        self.assertEqual(result.size,expected.size)

        for (ref,res) in zip(expected.flat,result.flat):
            self.assertAlmostEqual(ref,res)

    #-------------------------------------------------------------------------
    def trim_output(self,data):
        data = data.replace("'","")
        data = data.replace("\n"," ")
        
        return data.replace("  "," ")

    #-------------------------------------------------------------------------
    def get_total_result(self):
        result =  check_output(self.command+self.nxopts+self.rebin_opt+
                               ["fiodata.nxs"])
        result = self.trim_output(result)
        return result

    #-------------------------------------------------------------------------
    def get_total_result_norm(self):
        result =  check_output(self.command + self.nxopts + self.rebin_opt +  
                               ["--normalize","fiodata.nxs"])
        result = self.trim_output(result)
        return result

    #-------------------------------------------------------------------------
    def get_roi1_result(self):
        result =  check_output(self.command + [common.roi1_opt] + self.nxopts 
                               + self.rebin_opt + ["fiodata.nxs"])

        result = self.trim_output(result)
        return result

    #-------------------------------------------------------------------------
    def get_roi1_result_norm(self):
        result =  check_output(self.command + [common.roi1_opt] + self.nxopts 
                               + self.rebin_opt + ["--normalize", "fiodata.nxs"])

        result = self.trim_output(result)
        return result

    #-------------------------------------------------------------------------
    def get_roi2_result(self):
        result =  check_output(self.command + [common.roi2_opt] + self.nxopts 
                               + self.rebin_opt + ["fiodata.nxs"])

        result = self.trim_output(result)
        return result
    
    #-------------------------------------------------------------------------
    def get_roi2_result_norm(self):
        result =  check_output( self.command + [common.roi2_opt] + self.nxopts
                                + self.rebin_opt + ["--normalize","fiodata.nxs"])

        result = self.trim_output(result)
        return result

    #-------------------------------------------------------------------------
    def test_total(self):
        result = common.result_to_ndarray(self.get_total_result(),
                                          self.total_ref.size,
                                          dtype="float64",sep=" ")

        self.check_result(result,self.total_ref)

    #-------------------------------------------------------------------------
    def test_total_norm(self):
        result = common.result_to_ndarray(self.get_total_result_norm(),
                                          self.total_norm_ref.size,
                                          dtype="float64",sep=" ")

        self.check_result(result,self.total_norm_ref)

    #-------------------------------------------------------------------------
    def test_roi1(self):
        result = common.result_to_ndarray(self.get_roi1_result(),
                                          self.roi1_ref.size,
                                          dtype="float64",sep=" ")

        self.check_result(result,self.roi1_ref)

    #-------------------------------------------------------------------------
    def test_roi1_norm(self):
        result = common.result_to_ndarray(self.get_roi1_result_norm(),
                                          self.roi1_norm_ref.size,
                                          dtype="float64",sep=" ")

        self.check_result(result,self.roi1_norm_ref)

    #-------------------------------------------------------------------------
    def test_roi2(self):
        result = common.result_to_ndarray(self.get_roi2_result(),
                                          self.roi2_ref.size,
                                          dtype="float64",sep=" ")

        self.check_result(result,self.roi2_ref)
    
    #-------------------------------------------------------------------------
    def test_roi2_norm(self):
        result = common.result_to_ndarray(self.get_roi2_result_norm(),
                                          self.roi2_norm_ref.size,
                                          dtype="float64",sep=" ")

        self.check_result(result,self.roi2_norm_ref)

#=============================================================================
class mcaops_rebin_test_fio(mcaops_rebin_test):
    
    #-------------------------------------------------------------------------
    def get_total_result(self):
        result =  check_output(self.command + self.rebin_opt +
                               [common.files1,common.files2])
        result = self.trim_output(result)
        return result

    #-------------------------------------------------------------------------
    def get_total_result_norm(self):
        result =  check_output(self.command + self.rebin_opt + 
                               ["--normalize",common.files1,common.files2])
        result = self.trim_output(result)
        return result

    #-------------------------------------------------------------------------
    def get_roi1_result(self):
        result =  check_output(self.command + [common.roi1_opt] 
                               + self.rebin_opt + [common.files1,common.files2])
        result = self.trim_output(result)
        return result

    #-------------------------------------------------------------------------
    def get_roi1_result_norm(self):
        result =  check_output(self.command + [common.roi1_opt] 
                               + self.rebin_opt + 
                               ["--normalize", common.files1,common.files2])
        result = self.trim_output(result)
        return result
    #-------------------------------------------------------------------------
    def get_roi2_result(self):
        result = check_output(self.command + [common.roi2_opt]
                              + self.rebin_opt + 
                              [common.files1,common.files2])
        result = self.trim_output(result)
        return result
    
    #-------------------------------------------------------------------------
    def get_roi2_result_norm(self):
        result = check_output(self.command + [common.roi2_opt]
                              + self.rebin_opt + 
                              ["--normalize",common.files1,common.files2])
        result = self.trim_output(result)
        return result


#=============================================================================
class mcaops_rebin_test_stdio(mcaops_rebin_test):

    #-------------------------------------------------------------------------
    def get_total_result(self):
        
        result = ""
        for input_file in common.input_files:
            tail = Popen(["tail","-n2048",input_file],stdout=PIPE)
            result += check_output(self.command + self.rebin_opt,
                                   stdin=tail.stdout)

        result = self.trim_output(result)
        return result
    
    #-------------------------------------------------------------------------
    def get_total_result_norm(self):
        
        result = ""
        for input_file in common.input_files:
            tail = Popen(["tail","-n2048",input_file],stdout=PIPE)
            result += check_output(self.command + self.rebin_opt + 
                                   ["--normalize"],
                                    stdin=tail.stdout)

        result = self.trim_output(result)
        return result
    
    #-------------------------------------------------------------------------
    def get_roi1_result(self):
        result = ""
        for input_file in common.input_files:
            tail = Popen(["tail","-n2048",input_file],stdout=PIPE)
            result += check_output(self.command + [common.roi1_opt] + 
                                   self.rebin_opt,stdin=tail.stdout)
        
        result = self.trim_output(result)
        return result
    
    #-------------------------------------------------------------------------
    def get_roi1_result_norm(self):
        result = ""
        for input_file in common.input_files:
            tail = Popen(["tail","-n2048",input_file],stdout=PIPE)
            result += check_output(self.command + [common.roi1_opt] +
                                    self.rebin_opt + ["--normalize"],
                                    stdin=tail.stdout)
        
        result = self.trim_output(result)
        return result

    #-------------------------------------------------------------------------
    def get_roi2_result(self):
        result = ""
        for input_file in common.input_files:
            tail = Popen(["tail","-n2048",input_file],stdout=PIPE)
            result += check_output(self.command + [common.roi2_opt] + 
                                    self.rebin_opt,
                                    stdin=tail.stdout)

        result = self.trim_output(result)
        return result

    #-------------------------------------------------------------------------
    def get_roi2_result_norm(self):
        result = ""
        for input_file in common.input_files:
            tail = Popen(["tail","-n2048",input_file],stdout=PIPE)
            result += check_output(self.command + [common.roi2_opt] + 
                                    self.rebin_opt+ ["--normalize"],
                                    stdin=tail.stdout)

        result = self.trim_output(result)
        return result


#---------------------------run the program if necessary----------------------
if __name__ == "__main__":
    unittest.main()
