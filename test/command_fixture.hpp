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
#pragma once
#include <boost/filesystem.hpp>
#include <test/config.hpp>
#include <string>
#include <vector>

using option_list = std::vector<std::string>;


struct command_fixture
{
    boost::filesystem::path command_path;
    std::string command; 
    std::string output;
    int return_value;

    //
    // constructor
    //
    command_fixture();

    //
    // assemble the final command and execute it.
    //
    // Side effects: this function sets some of the members of the command
    //               fixture. Namely: 
    // *command
    // *output
    // *return_value
    void run_command(const option_list &options,
                     const boost::filesystem::path &tempfile=
                     boost::filesystem::path("output.tmp"));
};
