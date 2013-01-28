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
 * Created on: Jan 02, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <pni/core/config/configuration.hpp>
#include "command.hpp"

using namespace pni::core;

//! create something
class cmd_mkfield : public command
{
    private:
        std::unique_ptr<configuration> _config;

        template<typename ...ARGST>
        void mkfield(const nxgroup &g,const string &name,
                     const string &type,ARGST ...args) const;
    public:
        virtual void setup(const std::vector<string> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
        virtual void help() const;
};

//-----------------------------------------------------------------------------
template<typename ...ARGST>
void cmd_mkfield::mkfield(const nxgroup &g,const string &name,
                          const string &type,ARGST ...args) const
{

    if(type == "string")
        g.create_field<string>(name,args...);
    else if(type == "uint8")
        g.create_field<uint8>(name,args...);
    else if(type == "int8")
        g.create_field<int8>(name,args...);
    else if(type == "uint16")
        g.create_field<uint16>(name,args...);
    else if(type == "int16")
        g.create_field<int16>(name,args...);
    else if(type == "uint32")
        g.create_field<uint32>(name,args...);
    else if(type == "int32")
        g.create_field<int32>(name,args...);
    else if(type == "uint64")
        g.create_field<uint64>(name,args...);
    else if(type == "int64")
        g.create_field<int64>(name,args...);
    else if(type == "float32")
        g.create_field<float32>(name,args...);
    else if(type == "float64")
        g.create_field<float64>(name,args...);
    else if(type == "float128")
        g.create_field<float128>(name,args...);
    else if(type == "complex32")
        g.create_field<complex32>(name,args...);
    else if(type == "complex64")
        g.create_field<complex64>(name,args...);
    else if(type == "complex128")
        g.create_field<complex128>(name,args...);
    else
        std::cerr<<"Unknown type string!"<<std::endl;
}


