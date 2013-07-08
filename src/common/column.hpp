/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: Jun 13, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <pni/core/types.hpp>

using namespace pni::core;

/*!
\ingroup common_devel
\brief column template

This template class describes a single column in a table. A column can be
considered as a container (the concrete type is determined by the container type
CTYPE) and some metadata. This metadata includes: 

\li the name of the column
\li the data type of the elements
\li the shape of an element 

The container type is assumed to be one dimensional and supports the full STL
interface. In particular push_back support must be provided. Thus array types as
defined by libpnicore are not feasible as container types for this template.


\tparam CTYPE container type for the column
*/
template<typename CTYPE> class column
{
    public:
        //-----------------some public types------------------------------
        //! constant interator type
        typedef typename CTYPE::const_iterator const_iterator;
        //! iterator type
        typedef typename CTYPE::iterator iterator;
        //! value type
        typedef typename CTYPE::value_type value_type;
    private:
        CTYPE _container;
        string _name;
        string _unit;
    public: 
        //===================constructors and destructor========================
        //! default constructor
        column():
            _container(),
            _name(),
            _unit()
        {}

        //---------------------------------------------------------------------
        //! copy constructor
        column(const column<CTYPE> &c):
            _container(c._container),
            _name(c._name),
            _unit(c._unit)
        {}

        //---------------------------------------------------------------------
        //! move constructor
        column(column<CTYPE> &&c):
            _container(std::move(c._container)),
            _name(std::move(c._name)),
            _unit(std::move(c._unit))
        {}



        //===================assignment operators==============================
        //! copy assignment
        column<CTYPE> &operator=(const column<CTYPE> &c)
        {
            if(this == &c) return *this;
            *this = column<CTYPE>(c);

            return *this;
        }

        //---------------------------------------------------------------------
        //! move assignment
        column<CTYPE> &operator=(column<CTYPE> &&c)
        {
            if(this == &c) return *this;
            this->_container = std::move(c._container);
            this->_unit = std::move(c._unit);
            this->_name = std::move(c._name);
            return *this;
        }

        //======================public methods=================================
        //! return column name
        string name() const { return _name; }

        //---------------------------------------------------------------------
        //! set column name
        void name(const string &n) { _name = n; }

        //---------------------------------------------------------------------
        //! return unit 
        string unit() const { return _unit; }

        //---------------------------------------------------------------------
        //! set unit
        void unit(const string &u) { _unit = u; }

        //---------------------------------------------------------------------
        /*!
        \brief get shape

        Returns the shape of the objects stored in each cell of the column.
        \tparam STYPE container for shape
        \return instance of STYPE with the shape
        */
        template<typename STYPE> STYPE shape() const
        {
            return _container.front().template shape<STYPE>();
        }

        //---------------------------------------------------------------------
        //! get element type ID
        type_id_t type_id() const 
        {
            return _container.front().type_id();
        }

        //---------------------------------------------------------------------
        /*!
        \brief number of elements
        
        Return the number of elements stored in the column.
        \return number of elements
        */
        size_t size() const { return _container.size(); }

        //---------------------------------------------------------------------
        void push_back(const value_type &v)
        {
            _container.push_back(v);
        }

        //---------------------------------------------------------------------
        void push_back(value_type &&v)
        {
            _container.push_back(v);
        }
        

        //========================iterators methods============================
        //! get const iterator to first element
        const_iterator begin() const { return _container.begin(); }

        //---------------------------------------------------------------------
        //! get const iterator to last+1 element
        const_iterator end() const { return _container.end(); }

        //---------------------------------------------------------------------
        //! get iterator to first element
        iterator begin() { return _container.begin(); }

        //---------------------------------------------------------------------
        //! get iterator to last+1 element
        iterator end() { return _container.end(); }

};
        
//========================= creation functions==================================
/*!
\ingroup common_devel
\brief create column

Create an empty column for a particular container type. This function could have
been made a static method  of the class however, this would still cause some
coupling of the class.
\tparam CTYPE container type for the column
\param n name of the column
\param u unit of the stored data
\return instance of column
*/
template<typename CTYPE>
column<CTYPE> create_column(const string &n,const string &u)
{
    column<CTYPE> col;
    col.name(n);
    col.unit(u);
    return col;
}

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief create column

Create a column with initial data. The container can be anything that
supports full STL iterator interface.
\tparam CTYPE container type for the column
\tparam UC container type for initial data container
\param n name of the column
\param u unit of data
\param c container from which to copy data
\return instance of column
*/
template<typename UC,typename CTYPE>
column<CTYPE> create_column(const string &n,const string &u,const UC &c)
{
    column<CTYPE> col;
    col.name(n);
    col.unit(u);

    for(auto v: c)
        col.push_back(v);

    return col;
}

