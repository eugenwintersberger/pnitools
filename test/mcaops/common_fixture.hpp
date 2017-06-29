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

using result_t        = std::vector<float64>;
using parser_t        = parser<result_t>;
using result_parser_t = parser<sums_t>;

static result_parser_t result_parser;
static result_t total_results;
static result_t roi1_sums;
static result_t roi2_sums;

struct mcaops_global_fixture 
{

    mcaops_global_fixture()
    {
        result_parser = result_parser_t(container_io_config('\n'));
        total_sums = sum_parser(read_data(total_sum_file.string()));
        roi1_sums = sum_parser(read_data(roi1_sum_file.string())); 
        roi2_sums = sum_parser(read_data(roi2_sum_file.string()));
    }

    virtual ~mcaops_global_fixture()
    {}
};
