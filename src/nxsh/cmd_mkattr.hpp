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

//-----------------------------------------------------------------------------
//! create something
class cmd_mkattr : public command
{
    private:
        std::unique_ptr<configuration> _config;

        template<typename ...ATYPES>
            void mkattr(const NXObject &p,const String &name,
                        const String &type,ATYPES ...args) const;
    public:
        virtual void setup(const std::vector<String> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
        virtual void help() const;
};

template<typename ...ATYPES>
void cmd_mkattr::mkattr(const NXObject &o,const String &name,const String &type,
                        ATYPES ...args) const
{
    if(type == "string")
        o.attr<String>(name,args...);
    else if(type == "uint8")
        o.attr<UInt8>(name,args...);
    else if(type == "int8")
        o.attr<Int8>(name,args...);
    else if(type == "uint16")
        o.attr<UInt16>(name,args...);
    else if(type == "int16")
        o.attr<Int16>(name,args...);
    else if(type == "uint32")
        o.attr<UInt32>(name,args...);
    else if(type == "int32")
        o.attr<Int32>(name,args...);
    else if(type == "uint64")
        o.attr<UInt64>(name,args...);
    else if(type == "int64")
        o.attr<Int64>(name,args...);
    else if(type == "float32")
        o.attr<Float32>(name,args...);
    else if(type == "float64")
        o.attr<Float64>(name,args...);
    else if(type == "float128")
        o.attr<Float128>(name,args...);
    else if(type == "complex32")
        o.attr<Complex32>(name,args...);
    else if(type == "complex64")
        o.attr<Complex64>(name,args...);
    else if(type == "complex128")
        o.attr<Complex128>(name,args...);
    else
        std::cout<<"Unkonwn type string!"<<std::endl;

}


