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
#include <pni/core/Slice.hpp>
#include <pni/io/nx/NX.hpp>
#include <boost/lexical_cast.hpp>
#include <pni/core/array.hpp>


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
    return array(DArray<T>(s));
}

//-----------------------------------------------------------------------------
/*!
\brief create array 

Creates an array type erasure which holds the appropriate array for a particular
IO-object (which is typically either a field or a selection). Indeed, this
template function just dispatches the work to by evaluating the data type of
the IO-object and call the appropriate template version of another template
function.
\throws TypeError if data type of ioobj is not supported
\tparam IOT io-type
\param ioobj instance of IOT for which array should be created
\return instance of array
*/
template<typename IOT> array create_array(const IOT &ioobj)
{
    shape_t shape = ioobj.template shape<shape_t>();

    if(ioobj.type_id() == TypeID::UINT8) 
        return array_create<UInt8>(shape);
    else if(ioobj.type_id() == TypeID::INT8) 
        return array_create<Int8>(shape);
    else if(ioobj.type_id() == TypeID::UINT16)
        return array_create<UInt16>(shape);
    else if(ioobj.type_id() == TypeID::INT16)
        return array_create<Int16>(shape);
    else if(ioobj.type_id() == TypeID::UINT32)
        return array_create<UInt32>(shape);
    else if(ioobj.type_id() == TypeID::INT32)
        return array_create<Int32>(shape);
    else if(ioobj.type_id() == TypeID::UINT64)
        return array_create<UInt64>(shape);
    else if(ioobj.type_id() == TypeID::INT64)
        return array_create<Int64>(shape);
    else if(ioobj.type_id() == TypeID::FLOAT32)
        return array_create<Float32>(shape);
    else if(ioobj.type_id() == TypeID::FLOAT64)
        return array_create<Float64>(shape);
    else if(ioobj.type_id() == TypeID::FLOAT128)
        return array_create<Float128>(shape);
    else if(ioobj.type_id() == TypeID::COMPLEX32)
        return array_create<Complex32>(shape);
    else if(ioobj.type_id() == TypeID::COMPLEX64)
        return array_create<Complex64>(shape);
    else if(ioobj.type_id() == TypeID::COMPLEX128)
        return array_create<Complex128>(shape);
    else if(ioobj.type_id() == TypeID::STRING)
        return array_create<String>(shape);
    else
        throw TypeError(EXCEPTION_RECORD,"Unsupported data type!");

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
template<typename T,typename READT> array read_data(const READT &readable)
{
    //create the array object to hold the data
    array data = create_array(readable);

    //read data from the readable
    readable.read(data);

    //return the array type erasure
    return data;
}


//-----------------------------------------------------------------------------
template<typename READT
         typename = typename std::enable_if<
            std::is_same<NXField,typename std::remove_reference<READT>::type>::value
            ||
            std::is_same<NXSelection,typename std::remove<reference<READT>::type>::value
         >::type
        > 
std::ostream &write_data(std::ostream &stream,const READT &readable)
{
    array data = read_data(readable);
    stream<<data;
    return stream;
}

//-----------------------------------------------------------------------------
template<typename WRITET
         typename = typename std::enable_if<
            std::is_same<NXField,typename std::remove_reference<WRITET>::type>::value
            ||
            std::is_same<NXSelection,typename std::remove<reference<WRITET>::type>::value
         >::type
        > 
std::istream &read_data(std::istream &stream, const WRITET &writeable)
{
    array data = create_array(writeable);
    stream>>data;
    writeable.write(data);
    return stream;
}

//-----------------------------------------------------------------------------
/*!
\brief dump typed data

This template function finally finishes the job that was started by dump_field
template<typename T,typename READT> 
std::ostream &dump_data(std::ostream &os,const READT &field)
{
    typedef index_iterator<shape_t> iterator_t;
    T buffer;
    std::vector<Slice> slices;

    for(auto iter = iterator_t::begin(field.shape<shape_t>());
             iter!= iterator_t::end(field.shape<shape_t>());
             ++iter)
    {
        shape_t::const_iterator siter = iter->begin();
        for(Slice &slice: slices)
            slice = Slice(*siter++);

        const_cast<NXField&>(field)(slices).read(buffer);
        os<<buffer<<" ";
    }
    os<<std::endl;

    return os;
}


std::ostream &operator<<(std::ostream &o,const NXField &f);
std::istream &operator<<(std::istream &i,NXField &f);
*/

