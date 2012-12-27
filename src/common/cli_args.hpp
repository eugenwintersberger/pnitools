/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * pnitools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pnitools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: 19.12.2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <iostream>
#include <vector>
#include <pni/utils/Types.hpp>

extern "C"
{
#include<string.h>
}

using namespace pni::utils;

/*!
\brief class managing CLI options

This class is used to hold CLI options in a form convineant for the
program_options class. The intention of this class is to act as a exception save
container for custom built command line options that are generated from a
container of strings. The content of this string is than presented in way that
the program options class can parse it.
\code
std::list<std::string> strlist;

......code omitted .....

cli_args args(strlist);
program_config config;

......setup of config is omitted ....

config.parse(args.argc(),const_cast<char**>(args.argv()));
\endcode
Instances of cli_args are first class objects and do memory management by
themselfe. 
*/
class cli_args
{
    private:
        //! number of strings in the array below
        int _argc;
        //! pointers to the strings content
        char **_argv;
         
    public:
        //---------------------------------------------------------------------
        //! constructor 
        template<typename CTYPE> cli_args(const CTYPE &str_cont);

        //---------------------------------------------------------------------
        //! destructor
        ~cli_args();

        //---------------------------------------------------------------------
        //! get the argument values
        const char **argv()const;

        //---------------------------------------------------------------------
        //! get the number of arguments
        int argc() const;
};

//-----------------------------------------------------------------------------
template<typename CTYPE> cli_args::cli_args(const CTYPE &str_cont):
    _argc(str_cont.size()),
    _argv(new char*[str_cont.size()])
{
    size_t index = 0;
    for(auto v: str_cont)
    {
        //allocate memory 
        _argv[index] = new char[v.size()+1];

        //copy string
        strncpy(_argv[index],v.c_str(),v.size()+1); 
        
        index++; //increment argument index
    }

}

//-----------------------------------------------------------------------------
//! output operator
std::ostream &operator<<(std::ostream &ostr,const cli_args &args);
