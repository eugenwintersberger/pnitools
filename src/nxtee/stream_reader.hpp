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
 * Created on: Jul 18,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once
#include <iostream>
#include <pni/core/types.hpp>
#include <pni/io/nexus.hpp>

using namespace pni::core;
using namespace pni::io;
    
/*!
\brief stream writer visitor

This visitor reads data from a stream and writes it to a nexus object.
Naturally the target objects must be fields or attributes. However, due to some
limitations of HDF5 both objects have some small limitations. 

For attributes the stream is read until eof and than the data is written by
replaceing the original attribute. 

For fields (currently only 1D fields are supported) the data is appended to the
existing field.

\tparam VTYPE variant type
*/
template<typename VTYPE> 
class stream_writer_visitor : public boost::static_visitor<void>
{
    public:
        //! first data type of the variant type
        typedef typename nxvariant_member_type<VTYPE,0>::type first_member;
        //! result type
        typedef void result_type;
        //! Nexus group type
        DEFINE_NXGROUP(first_member) group_type;
        //! Nexus field type
        DEFINE_NXFIELD(first_member) field_type;
        //! Nexus attribute type
        DEFINE_NXATTRIBUTE(first_member) attribute_type;
    private:
        std::istream &_stream; //!< the inputstream from which to read data

        //=============some private member functions========================
        template<typename T> void append_from_stream(const field_type &f)
        {
            T value;
            while(_stream>>value)
            {
                grow(f,0);
                write(f,value,get_size(f)-1);
            }
        }

        //---------------------------------------------------------------------
        void apepnd_from_stream(const field_type &f);
    public:

        //-----------------------------------------------------------------
        /*!
        \brief constructor

        \param s class type
        */
        stream_writer_visitor(std::istream &s):_stream(s) {}
       
        //-----------------------------------------------------------------
        /*!
        \brief process groups

        Throw an exeption as one cannot write data to a group.
        \throws nxgroup_error if NX_class attribute does not exist
        \param g group instance
        \return true if class types match, false otherwise
        */
        result_type operator()(const group_type &g);

        //-----------------------------------------------------------------
        /*!
        \brief process fields
        
        As fields do not have a class type this method throws an exception. 
        \throws nxfield_error fields do not have a class
        \param f field instance
        \return can be ignored 
        */
        result_type operator()(const field_type &f);

        //----------------------------------------------------------------
        /*!
        \brief process attributes

        Attributes do not have a class type. Thus this method throws an
        exception. 
        \throws nxattribute_error attributes have no class
        \param a attribute instance
        \return can be ignored
        */
        result_type operator()(const attribute_type &a);
};

//================Implementation of class member functions=====================

template<typename VTYPE>
void stream_writer_visitor<VTYPE>::append_from_stream
(const typename stream_writer_visitor<VTYPE>::field_type &f)
{
    if(f.type_id() == type_id_t::UINT8) append_from_stream<uint8>(f);
    else if(f.type_id() == type_id_t::INT8) append_from_stream<int8>(f);
    else if(f.type_id() == type_id_t::UINT16) append_from_stream<uint16>(f);
    else if(f.type_id() == type_id_t::INT16) append_from_stream<int16>(f);
    else if(f.type_id() == type_id_t::UINT32) append_from_stream<uint32>(f);
    else if(f.type_id() == type_id_t::INT32) append_from_stream<int32>(f);
    else if(f.type_id() == type_id_t::UINT64) append_from_stream<uint64>(f);
    else if(f.type_id() == type_id_t::INT64) append_from_stream<int64>(f);
    else if(f.type_id() == type_id_t::FLOAT32) append_from_stream<float32>(f);
    else if(f.type_id() == type_id_t::FLOAT64) append_from_stream<float64>(f);
    else if(f.type_id() == type_id_t::FLOAT128) append_from_stream<float128>(f);
    else if(f.type_id() == type_id_t::STRING) append_from_stream<

    
}

//-----------------------------------------------------------------------------
template<typename VTYPE>
typename stream_writer_visitor<VTYPE>::result_type
stream_writer_visitor<VTYPE>::operator()
(const typename stream_writer_visitor<VTYPE>::group_type &g)
{
    throw nxgroup_error(EXCEPTION_RECORD,
            "Cannot appen data to a group!");

    return result_type();

}
//-----------------------------------------------------------------------------
template<typename VTYPE>
typename stream_writer_visitor<VTYPE>::result_type
stream_writer_visitor<VTYPE>::operator()
(const typename stream_writer_visitor<VTYPE>::field_type &f)
{
    if(f.rank()!=1)
        throw nxfield_error(EXCEPTION_RECORD,
                "Cannot write stream to a multidimensional field!");

    append_from_stream(f);
    return result_type();
}
//-----------------------------------------------------------------------------
template<typename VTYPE> 
typename stream_writer_visitor<VTYPE>::result_type
stream_writer_visitor<VTYPE>::operator()
(const typename stream_writer_visitor<VTYPE>::attribute_type &a)
{

    return result_type();
}


//================Implementation of the wrapper function=======================
/*!
\ingroup variant_code
\brief is class wrapper 

Wrapper function for the is_class_visitor template. 

\throws nxgroup_error if group does not have an NX_class attribute
\throws nxfield_error if the stored object is a field
\throws nxattribute_error if the stored object is an attribute
\tparam VTYPE variant type
\param o instance of VTYPE
\param c Nexus class to check for
\return true if group class and c match, false otherwise
*/
template<typename VTYPE> 
typename is_class_visitor<VTYPE>::result_type 
is_class(const VTYPE &o,const string &c)
{
    return boost::apply_visitor(is_class_visitor<VTYPE>(c),o);
}


