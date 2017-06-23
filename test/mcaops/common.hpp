//
// (c) Copyright 2017 DESY
//
// This file is part of pniio.
//
// pniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pniio.  If not, see <http://www.gnu.org/licenses/>.
// 
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created: Thu 22 Jun, 2017
//
#pragma once
#include <boost/filesystem.hpp>
#include <string>
#include <vector>

static const std::string roi1_opt = "--roi=5:501";
static const std::string roi2_opt = "--roi=1024:2013";
static const std::string base_opt = "--base=/:NXentry/:NXinstrument/:NXdetector";
static const std::string mca_opt = "-mdata";

static const std::string filename_format = "scan_mca_%05i.fio";
static const std::string file_range_1 = ":1:11";
static const std::string file_range_2 = ":42:96";

static const boost::filesystem::path total_sum_file("total_sum.dat");
static const boost::filesystem::path roi1_sum_file("roi1_sum.dat");
static const boost::filesystem::path roi2_sum_file("roi2_sum.dat");

static const boost::filesystem::path total_min_file("total_min.dat");
static const boost::filesystem::path roi1_min_file("roi1_min.dat");
static const boost::filesystem::path roi2_min_file("roi2_min.dat");

static const boost::filesystem::path total_max_file("total_max.dat");
static const boost::filesystem::path roi1_max_file("roi1_max.dat");
static const boost::filesystem::path roi2_max_file("roi2_max.dat");

static const boost::filesystem::path total_argmin_file("total_argmin.dat");
static const boost::filesystem::path roi1_argmin_file("roi1_argmin.dat");
static const boost::filesystem::path roi2_argmin_file("roi2_argmin.dat");

static const boost::filesystem::path total_argmax_file("total_argmax.dat");
static const boost::filesystem::path roi1_argmax_file("roi1_argmax.dat");
static const boost::filesystem::path roi2_argmax_file("roi2_argmax.dat");

static const boost::filesystem::path total_average_file("total_average.dat");
static const boost::filesystem::path roi1_average_file("roi1_average.dat");
static const boost::filesystem::path roi2_average_file("roi2_average.dat");

static const std::vector<boost::filesystem::path> stdin_files = {
    boost::filesystem::path("scan_mca_00001.txt"),
    boost::filesystem::path("scan_mca_00002.txt"),
    boost::filesystem::path("scan_mca_00003.txt"),
    boost::filesystem::path("scan_mca_00004.txt"),
    boost::filesystem::path("scan_mca_00005.txt"),
    boost::filesystem::path("scan_mca_00006.txt"),
    boost::filesystem::path("scan_mca_00007.txt"),
    boost::filesystem::path("scan_mca_00008.txt"),
    boost::filesystem::path("scan_mca_00009.txt"),
    boost::filesystem::path("scan_mca_00010.txt")};


