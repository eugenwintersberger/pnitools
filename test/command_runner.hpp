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

#include <string>
#include <vector>
#include <boost/filesystem.hpp>

using cmd_opts_t = std::vector<std::string>;

class command_runner
{
    private:
        std::string _cmd;
        std::string _output;
        int         _return;

        std::string _assemble_command(const cmd_opts_t &opts);
        std::string _read_output(const boost::filesystem::path& tmpfile);
    public:

        command_runner(const boost::filesystem::path &command);


        int operator()(const cmd_opts_t &user_options,
                       const boost::filesystem::path &tmpfile = 
                       boost::filesystem::path("output.tmp"));

        std::string output() const;
        int return_value() const;
};


