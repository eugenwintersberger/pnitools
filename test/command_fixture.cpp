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
// Created: Thu 22 Jan, 2017
//
#include <test/command_fixture.hpp>

namespace fs = boost::filesystem;

command_fixture::command_fixture():
    command_path(bin_path),
    command(),
    output(),
    return_value()
{}


void command_fixture::run_command(const option_list &options,
                                  const fs::path &tempfile)
{
    std::vector<std::string> l{command_path.string()};
    std::copy(options.begin(),options.end(),std::back_inserter(l));
    l.push_back(">"+tempfile.string());
    
    command = get_command(l);
    return_value = std::system(command.c_str());
    output = read_data(tempfile);
}

