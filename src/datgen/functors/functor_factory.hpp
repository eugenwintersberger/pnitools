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
#pragma once

#include <pni/core/types.hpp>
#include "functor.hpp"
#include "../options_splitter.hpp"

//! 
//! \ingroup datgen_devel
//! \brief functor factory class
//! 
//! This class is used to create concrete functors. It is stateless and all 
//! work is done via static member functions.
//! 
class functor_factory
{
    private:
        static functor::pointer_type create_uniform(const args_vector &args);
        static functor::pointer_type create_linear(const args_vector &args);
        static functor::pointer_type create_gauss(const args_vector &args);
    public:
        static functor::pointer_type create(const pni::core::string &name,
                                            const args_vector &args);
};
