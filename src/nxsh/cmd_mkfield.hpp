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

#include <pni/utils/config/configuration.hpp>
#include "command.hpp"

using namespace pni::utils;

//! create something
class cmd_mkfield : public command
{
    private:
        std::unique_ptr<configuration> _config;

        shape_t read_shape(const String &s) const;
        template<typename ...ARGST>
        void mkfield(const NXGroup &g,const String &name,
                     const String &type,ARGST ...args) const;
    public:
        virtual void setup(const std::vector<String> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
        virtual void help() const;
};

template<typename ...ARGST>
void cmd_mkfield::mkfield(const NXGroup &g,const String &name,
                          const String &type,ARGST ...args) const
{

    if(type == "string")
        g.create_field<String>(name,args...);
    else if(type == "uint8")
        g.create_field<UInt8>(name,args...);
    else if(type == "int8")
        g.create_field<Int8>(name,args...);
    else if(type == "uint16")
        g.create_field<UInt16>(name,args...);
    else if(type == "int16")
        g.create_field<Int16>(name,args...);
    else if(type == "uint32")
        g.create_field<UInt32>(name,args...);
    else if(type == "int32")
        g.create_field<Int32>(name,args...);
    else if(type == "uint64")
        g.create_field<UInt64>(name,args...);
    else if(type == "int64")
        g.create_field<Int64>(name,args...);
    else if(type == "float32")
        g.create_field<Float32>(name,args...);
    else if(type == "float64")
        g.create_field<Float64>(name,args...);
    else if(type == "float128")
        g.create_field<Float128>(name,args...);
    else if(type == "complex32")
        g.create_field<Complex32>(name,args...);
    else if(type == "complex64")
        g.create_field<Complex64>(name,args...);
    else if(type == "complex128")
        g.create_field<Complex128>(name,args...);
    else
        std::cerr<<"Unknown type string!"<<std::endl;
}


