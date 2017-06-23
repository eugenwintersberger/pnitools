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
// Created: Fri 23 Jun, 2017
//
#pragma once

#include <pni/core/types.hpp>
#include <pni/io/parsers.hpp>
#include <vector>
#include <test/command_runner.hpp>

struct datgen_fixture
{
    using result_t = std::vector<pni::core::float64>;
    using parser_t = pni::io::parser<pni::core::float64>;


    command_runner runner;
    parser_t result_parser;
    result_t x;
    result_t y;

    datgen_fixture();
    void read_results(); 

};


