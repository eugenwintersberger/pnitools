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
 * Created on: Sep 26, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once
#include<pni/utils/Types.hpp>
#include<pni/utils/Exceptions.hpp>

using namespace pni::utils;

/*!
\brief file type error

This exception is thrown if the input or output file format cannot be
handled.
*/
class file_type_error:public Exception
{
    public:
        //-----------------------------------------------------------------
        //! default constructor
        file_type_error():Exception("FileTypeError"){}
        
        //-----------------------------------------------------------------
        /*!
        \brief constructor

        \param r exception record
        \param d description
        */
        file_type_error(const ExceptionRecord &r,const String &d):
            Exception("FileTypeError",r,d)
        {}

        //-----------------------------------------------------------------
        //! destructor
        ~file_type_error() throw() {}

        //! output operator
        friend std::ostream &operator<<(std::ostream &o,const file_type_error &e);
};
