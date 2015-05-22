//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// libpniutils is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniutils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
// Created on: May 21, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include "index_generator.hpp"
#include "../operation.hpp"

class data_provider
{
    private:
        index_generator _index_gen;
    public:
        typedef std::unique_ptr<data_provider> pointer_type;
        typedef operation::argument_type       value_type;

        data_provider();
        data_provider(const index_generator &g);
        virtual ~data_provider();


        virtual bool finished() const = 0;

        virtual value_type next()  = 0;

        index_generator create_generator() const;


    
};
