/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: 03.06.2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <iostream>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>

using namespace pni::core;

/*!
\brief base class for operations

This class provides the basic interface for all operations (commands) that can
be performed with mcaops.
*/
class operation
{
    private:
        bool _verbose;
    public:
        //=================public types========================================
        //! general array type
        typedef darray<float64> array_type;
        //! numeric array type
        typedef numarray<array_type> narray_type;
        //! shape type
        typedef shape_t shape_type;
        //---------------------------------------------------------------------
        operation():_verbose(false){}

        //---------------------------------------------------------------------
        virtual ~operation() {}

        //---------------------------------------------------------------------
        bool verbose() const { return _verbose; }

        //---------------------------------------------------------------------
        void verbose(bool v) { _verbose = v; }

        //---------------------------------------------------------------------
        virtual void operator()(const array_type &channels,
                                const array_type &data) = 0;

        //---------------------------------------------------------------------
        virtual std::ostream &stream_result(std::ostream &o) const = 0;
};

//-----------------------------------------------------------------------------
//! write operation to output stream
std::ostream &operator<<(std::ostream &o,const operation &op);

