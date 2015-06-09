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

using namespace pni::core;

//----------------------------------------------------------------------------
functor::pointer_type functor_factory::create_uniform(const args_vector &args)
{
    
    return functor::pointer_type();
}

//----------------------------------------------------------------------------
functor::pointer_type functor_factory::create_linear(const args_vector &args)
{
    return functor::pointer_type();
}

//----------------------------------------------------------------------------
functor::pointer_type functor_factory::create_gauss(const args_vector &args)
{
    
    return functor::pointer_type();
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
