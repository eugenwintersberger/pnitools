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
\brief utility function

Creates and instance of DArray for holding data for a particular readable type. 

*/
template<typename T,typename IOT>  DArray<T> create_array(const IOT &ioobj)
{
    shape_t shape = ioobj.template shape<shape_t>();

    return DArray<T>(shape_t);
}

//-----------------------------------------------------------------------------
/*!
\brief get data from readable 

\tparam T data type to use for reading
\tparam READT type of the readable from which to obtain the data
\param readable reference to the readable instance
\return instance of array
*/
template<typename T,typename READT> array get_data(const READT &readable)
{
    //create the array object to hold the data
    DArray<T> data = create_array<T>(readable);

    //read data from the readable
    readable.read(data);

    //return the array type erasure
    return array(std::move(data));
}

//-----------------------------------------------------------------------------
/*!
\brief read data

Reads data from an instance of a readable type and stores the result in an array
type erasure. If the type of the readable is not know an exception will be
thrown. This template function only decides which data type to use to read the
data. The reading of the data is defered to the get_data template function.

\throws TypeError if data type cannot be handled
\tparam READT readable type
\param readable instance of READT from which to read data
\return instance of array
*/
template<typename READT> array read_data(const READT &readable)
{
    typedef index_iterator<shape_t> iterator_t; 

    if(readable.type_id() == TypeID::UINT8)
        return get_data<UInt8>(readable);
    else if(readable.type_id() == TypeID::INT8)
        return get_data<Int8>(readable);
    else if(readable.type_id() == TypeID::UINT16)
        return get_data<UInt16>(readable);
    else if(readable.type_id() == TypeID::INT16)
        return get_data<Int16>(readable);
    else if(readable.type_id() == TypeID::UINT32)
        return get_data<UInt32>(readable);
    else if(readable.type_id() == TypeID::INT32)
        return get_data<Int32>(readable);
    else if(readable.type_id() == TypeID::UINT64)
        return get_data<UInt64>(readable);
    else if(readable.type_id() == TypeID::INT64)
        return get_data<Int64>(readable);

    else if(readable.type_id() == TypeID::FLOAT32)
        return get_data<Float32>(readable);
    else if(readable.type_id() == TypeID::FLOAT64)
        return get_data<Float64>(readable);
    else if(readable.type_id() == TypeID::FLOAT128)
        return get_data<Float128>(readable);

    else if(readable.type_id() == TypeID::COMPLEX32)
        return get_data<Complex32>(readable);
    else if(readable.type_id() == TypeID::COMPLEX64)
        return get_data<Complex64>(readable);
    else if(readable.type_id() == TypeID::COMPLEX128)
        return get_data<Complex128>(readable);

    else if(readable.type_id() == TypeID::STRING)
        return get_data<String>(readable);
    else
        throw TypeError(EXCEPTION_RECORD,"Unknown data type in field");

    return array(); //just to make the compiler happy - code will never be reached
}

template<typename READT> std::ostream &write_data(std::ostream &stream,
                                                  const READT &readable);

template<typename WRITET> std::istream &read_data(std::istream &stream,
                                                  const WRITET &writeable)
{

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

