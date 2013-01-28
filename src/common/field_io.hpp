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
 * Created on: Jan 8, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <iostream>
#include <vector>
#include <pni/core/index_iterator.hpp>
#include <pni/core/slice.hpp>
#include <pni/io/nx/nx.hpp>
#include <boost/lexical_cast.hpp>
#include <pni/core/arrays.hpp>


using namespace pni::core;
using namespace pni::io::nx::h5;

/*!
\brief create array

Creates an instance of array using a DArray template with type T as its content. 
The shape of the array is passed by the user.
\tparam T data type of the array
\param s shape of the array
\return instance of array
*/
template<typename T> array create_array(shape_t s)
{
    return array(darray<T>(s));
}

//-----------------------------------------------------------------------------
/*!
\brief create array 

Creates an array type erasure which holds the appropriate array for a particular
IO-object (which is typically either a field or a selection). Indeed, this
template function just dispatches the work to by evaluating the data type of
the IO-object and call the appropriate template version of another template
function.
\throws type_error if data type of ioobj is not supported
\tparam IOT io-type
\param ioobj instance of IOT for which array should be created
\return instance of array
*/
template<typename IOT> array create_array(const IOT &ioobj)
{
    shape_t shape = ioobj.template shape<shape_t>();

    if(ioobj.type_id() == type_id_t::UINT8) 
        return create_array<uint8>(shape);
    else if(ioobj.type_id() == type_id_t::INT8) 
        return create_array<int8>(shape);
    else if(ioobj.type_id() == type_id_t::UINT16)
        return create_array<uint16>(shape);
    else if(ioobj.type_id() == type_id_t::INT16)
        return create_array<int16>(shape);
    else if(ioobj.type_id() == type_id_t::UINT32)
        return create_array<uint32>(shape);
    else if(ioobj.type_id() == type_id_t::INT32)
        return create_array<int32>(shape);
    else if(ioobj.type_id() == type_id_t::UINT64)
        return create_array<uint64>(shape);
    else if(ioobj.type_id() == type_id_t::INT64)
        return create_array<int64>(shape);
    else if(ioobj.type_id() == type_id_t::FLOAT32)
        return create_array<float32>(shape);
    else if(ioobj.type_id() == type_id_t::FLOAT64)
        return create_array<float64>(shape);
    else if(ioobj.type_id() == type_id_t::FLOAT128)
        return create_array<float128>(shape);
    /*
    else if(ioobj.type_id() == TypeID::COMPLEX32)
        return create_array<Complex32>(shape);
    else if(ioobj.type_id() == TypeID::COMPLEX64)
        return create_array<Complex64>(shape);
    else if(ioobj.type_id() == TypeID::COMPLEX128)
        return create_array<Complex128>(shape);
    else if(ioobj.type_id() == TypeID::STRING)
        return create_array<String>(shape);
    */
    else
        throw type_error(EXCEPTION_RECORD,"Unsupported data type!");

    return array(); //just to make the compiler happy

}

//-----------------------------------------------------------------------------
/*!
\brief get data from readable 

\tparam T data type to use for reading
\tparam READT type of the readable from which to obtain the data
\param readable reference to the readable instance
\return instance of array
*/
template<typename READT> array read_data(const READT &readable)
{
    //create the array object to hold the data
    array data = create_array(readable);

    //read data from the readable
    readable.read(data);

    //return the array type erasure
    return data;
}


//-----------------------------------------------------------------------------
template<typename READT,
         typename = typename std::enable_if<
            std::is_same<nxfield,typename std::remove_reference<READT>::type>::value
            ||
            std::is_same<nxselection,typename std::remove_reference<READT>::type>::value
            ||
            std::is_same<nxattribute,typename std::remove_reference<READT>::type>::value
         >::type
        > 
std::ostream &operator<<(std::ostream &stream,const READT &readable)
{
    array data = read_data(readable);
    stream<<data;
    return stream;
}

//-----------------------------------------------------------------------------
template<typename WRITET,
         typename = typename std::enable_if<
            std::is_same<nxfield,typename std::remove_reference<WRITET>::type>::value
            ||
            std::is_same<nxselection,typename std::remove_reference<WRITET>::type>::value
            ||
            std::is_same<nxattribute,typename std::remove_reference<WRITET>::type>::value
         >::type
        > 
std::istream &operator>>(std::istream &stream,WRITET &writeable)
{
    array data = create_array(writeable);
    stream>>data;
    writeable.write(data);
    return stream;
}

