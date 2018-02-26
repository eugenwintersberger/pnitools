//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// pnitools is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pnitools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//  Created on: Jun 20, 2017
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <test/config.hpp>
#include <iterator>
#include <sstream>
#include <pni/io/nexus.hpp>
#include <h5cpp/hdf5.hpp>

namespace fs = boost::filesystem;


std::string get_command(const std::vector<std::string> &l)
{
    std::string command;

    for(const std::string &value: l)
        command += " "+value;

    return command;
}

std::string read_data(const fs::path &filename)
{
    std::ifstream stream(filename.string());


    std::string data;

    while(!stream.eof())
    {
        std::string linebuffer;
        std::getline(stream,linebuffer);
        data += linebuffer+"\n"; 
    }

    return data;
}


std::string string_diff(const std::string &a,const std::string &b)
{
    std::stringstream ss;
    auto a_iter = a.begin();
    auto b_iter = b.begin();
    
    size_t position=0;
    for(;a_iter!=a.end() && b_iter!=b.end();a_iter++,b_iter++,position++)
    {
        if(*a_iter != *b_iter)
        {
            ss<<position<<"\t"<<*a_iter<<"\t"<<*b_iter<<std::endl;
        }

    }

    return ss.str();
}

int get_return_value(int return_value)
{
#ifdef _MSC_VER
    return return_value;
#else
    return WEXITSTATUS(return_value);
#endif
}

void create_file_from_xml(const fs::path &filename,const fs::path &xmlfile)
{
    using namespace pni::io;
    hdf5::file::File f =nexus::create_file(filename.string(),
    		                               hdf5::file::AccessFlags::TRUNCATE);
    nexus::xml::create_from_file(f.root(),xmlfile);
}
