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
// Created on: Jun 9, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "functor_factory.hpp"
#include "uniform.hpp"
#include "gauss.hpp"
#include "linear.hpp"

using namespace pni::core;

configuration functor_factory::create_uniform_config()
{
    configuration c;
    c.add_option(config_option<float64>("upper","u",
                "Upper bound of uniform distribution",1.0));
    c.add_option(config_option<float64>("lower","l",
                "Lower bound of uniform distribution",0.0));

    return c;
}

//----------------------------------------------------------------------------
functor::pointer_type functor_factory::create_uniform(const args_vector &args)
{
    configuration c = create_uniform_config();
    parse(c,args);

    return functor::pointer_type(
            new uniform(c.value<float64>("lower"),c.value<float64>("upper"))
            );
}

//---------------------------------------------------------------------------
configuration functor_factory::create_gauss_config()
{
    configuration c;
    c.add_option(config_option<float64>("sigma","s",
                "Sigma parameter of the Gaussian",1.0));
    c.add_option(config_option<float64>("mu","m",
                "Center parameter of the Gaussian",0.0));
    c.add_option(config_option<float64>("amplitude","a",
                "Amplitude of the Gaussian",1.0));
    return c;
}

//----------------------------------------------------------------------------
functor::pointer_type functor_factory::create_gauss(const args_vector &args)
{
    configuration c = create_gauss_config();

    parse(c,args);

    return functor::pointer_type(
            new gauss(c.value<float64>("sigma"),
                      c.value<float64>("mu"),
                      c.value<float64>("amplitude"))
            );
}

//----------------------------------------------------------------------------
configuration functor_factory::create_linear_config()
{
    configuration c;
    c.add_option(config_option<float64>("slope","s",
                "Slope of the linear function",1.0));
    c.add_option(config_option<float64>("offset","o",
                "Offset of the linear function",0.0));

    return c;
}

//----------------------------------------------------------------------------
functor::pointer_type functor_factory::create_linear(const args_vector &args)
{
    configuration c = create_linear_config();
    parse(c,args);

    return functor::pointer_type(
            new linear(c.value<float64>("slope"),
                       c.value<float64>("offset"))
            );
}

//----------------------------------------------------------------------------
functor::pointer_type functor_factory::create(const string &name,
                                              const args_vector &args)
{
    if(name == "uniform")
        return create_uniform(args);
    else if(name == "linear")
        return create_linear(args);
    else if(name == "gauss")
        return create_gauss(args);
    else
        throw key_error(EXCEPTION_RECORD,
                "Unknown function key ["+name+"]!");
}

//----------------------------------------------------------------------------
configuration functor_factory::config(const string &name)
{
    if(name == "uniform")     return create_uniform_config();
    else if(name == "linear") return create_linear_config();
    else if(name == "gauss")  return create_gauss_config();
    else 
        throw key_error(EXCEPTION_RECORD,
                "Unkonwn function key ["+name+"]!");
}
