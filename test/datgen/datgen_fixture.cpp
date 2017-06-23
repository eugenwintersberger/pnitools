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

#include "datgen_fixture.hpp"
#include <boost/filesystem.hpp>
#include <sstream>
#include <boost/algorithm/string/trim.hpp>
#include <test/config.hpp>

namespace fs = boost::filesystem;
using namespace pni::core;
using namespace pni::io;


datgen_fixture::datgen_fixture():
    runner(fs::path(bin_path).append("datgen")),
    result_parser(),
    x(),
    y()
{}

void datgen_fixture::read_results()
{
    x = result_t();
    y = result_t();
    std::string buffer(runner.output());
    boost::trim(buffer);
    std::stringstream stream(buffer);

    while(!stream.eof())
    {
        float64 x_i,y_i;
        stream>>x_i>>y_i;
        x.push_back(x_i);
        y.push_back(y_i);
    }
}
    

