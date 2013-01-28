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

#include <pni/core/config/cli_args.hpp>
#include <pni/core/config/config_parser.hpp>

//-----------------------------------------------------------------------------
void cmd_cat::setup(const std::vector<string> &cargs)
{
    _config = std::unique_ptr<configuration>(new configuration);
    _config->add_argument(config_argument<string>("sources",-1,"input fields"));

    cli_args args(cargs);
    parse(*_config,args.argc(),args.argv());
}

//-----------------------------------------------------------------------------
void cmd_cat::execute(std::unique_ptr<environment> &env)
{
    const nxgroup &cg = env->current_group();
    nxobject o = cg[_config->value<string>("sources")];

    if(o.object_type() == pni::io::nx::nxobject_type::NXFIELD)
    {
        nxfield f(o);
        
        if(f.type_id() == type_id_t::STRING) print_field<string>(f);
        else if(f.type_id() == type_id_t::UINT8) print_field<uint8>(f);
        else if(f.type_id() == type_id_t::INT8) print_field<int8>(f);
        else if(f.type_id() == type_id_t::UINT16) print_field<uint16>(f);
        else if(f.type_id() == type_id_t::INT16) print_field<int16>(f);
        else if(f.type_id() == type_id_t::UINT32) print_field<uint32>(f);
        else if(f.type_id() == type_id_t::INT32) print_field<int32>(f);
        else if(f.type_id() == type_id_t::UINT64) print_field<uint64>(f);
        else if(f.type_id() == type_id_t::INT64) print_field<int64>(f);
        else if(f.type_id() == type_id_t::FLOAT32) print_field<float32>(f);
        else if(f.type_id() == type_id_t::FLOAT64) print_field<float64>(f);
        else if(f.type_id() == type_id_t::FLOAT128) print_field<float128>(f);
        else if(f.type_id() == type_id_t::COMPLEX32) print_field<complex32>(f);
        else if(f.type_id() == type_id_t::COMPLEX64) print_field<complex64>(f);
        else if(f.type_id() == type_id_t::COMPLEX128) print_field<complex128>(f);
    }
    else
        std::cout<<"input is not a field"<<std::endl;

}

//-----------------------------------------------------------------------------
void cmd_cat::help() const
{
    std::cout<<*_config<<std::endl;
}
