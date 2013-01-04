/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: Jan 04, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "cmd_cat.hpp"

#include <pni/utils/config/cli_args.hpp>
#include <pni/utils/config/config_parser.hpp>



//-----------------------------------------------------------------------------
void cmd_cat::setup(const std::vector<String> &cargs)
{
    _config = std::unique_ptr<configuration>(new configuration);
    _config->add_argument(config_argument<String>("sources",-1,"input fields"));

    cli_args args(cargs);
    parse(*_config,args.argc(),args.argv());
}

//-----------------------------------------------------------------------------
void cmd_cat::execute(std::unique_ptr<environment> &env)
{
    const NXGroup &cg = env->current_group();
    NXObject o = cg[_config->value<String>("sources")];

    if(o.object_type() == pni::nx::NXObjectType::NXFIELD)
    {
        NXField f(o);
        
        if(f.type_id() == TypeID::STRING) print_field<String>(f);
        else if(f.type_id() == TypeID::UINT8) print_field<UInt8>(f);
        else if(f.type_id() == TypeID::INT8) print_field<Int8>(f);
        else if(f.type_id() == TypeID::UINT16) print_field<UInt16>(f);
        else if(f.type_id() == TypeID::INT16) print_field<Int16>(f);
        else if(f.type_id() == TypeID::UINT32) print_field<UInt32>(f);
        else if(f.type_id() == TypeID::INT32) print_field<Int32>(f);
        else if(f.type_id() == TypeID::UINT64) print_field<UInt64>(f);
        else if(f.type_id() == TypeID::INT64) print_field<Int64>(f);
        else if(f.type_id() == TypeID::FLOAT32) print_field<Float32>(f);
        else if(f.type_id() == TypeID::FLOAT64) print_field<Float64>(f);
        else if(f.type_id() == TypeID::FLOAT128) print_field<Float128>(f);
        else if(f.type_id() == TypeID::COMPLEX32) print_field<Complex32>(f);
        else if(f.type_id() == TypeID::COMPLEX64) print_field<Complex64>(f);
        else if(f.type_id() == TypeID::COMPLEX128) print_field<Complex128>(f);
    }
    else
        std::cout<<"input is not a field"<<std::endl;

}

//-----------------------------------------------------------------------------
void cmd_cat::help() const
{
    std::cout<<*_config<<std::endl;
}
