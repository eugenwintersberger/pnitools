//
// (c) Copyright  2017 DESY
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

#include "command_runner.hpp"
#include <fstream>
#include <iterator>
#include <cstdlib>

namespace fs = boost::filesystem;

//============================================================================
command_runner::command_runner(const fs::path &command):
    _cmd(command.string()),
    _output(),
    _return()
{}

//============================================================================
std::string command_runner::_assemble_command(const cmd_opts_t &opts)
{
    std::string command;

    for(const std::string &value: opts)
        command += " "+value;

    return command;
}

//============================================================================
std::string command_runner::_read_output(const fs::path &tmpfile)
{
    std::ifstream stream(tmpfile.string());


    std::string data;

    while(!stream.eof())
    {
        std::string linebuffer;
        std::getline(stream,linebuffer);
        data += linebuffer+"\n"; 
    }

    return data;
}

//============================================================================
int command_runner::operator()(const cmd_opts_t& user_options,
                               const fs::path &tmpfile)
{
    cmd_opts_t total_opts{_cmd};
    std::copy(user_options.begin(),user_options.end(),
              std::back_inserter(total_opts));
    total_opts.push_back(">"+tmpfile.string());
    
    _return = std::system(_assemble_command(total_opts).c_str());
    _output = _read_output(tmpfile);

    return return_value();
}

//============================================================================
std::string command_runner::output() const
{
    return _output;
}

//============================================================================
int command_runner::return_value() const
{
#ifdef _MSC_VER
    return _return;
#else
    return WEXITSTATUS(_return);
#endif
}

