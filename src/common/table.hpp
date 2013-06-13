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

#include <map>
#include <pni/core/types.hpp>

using namespace pni::core;

/*!
\ingroup common_devel
\brief table class

A table is a collection of columns. 
*/
template<typename COLTYPE> class table
{
    public:
        typedef COLTYPE column_type;
    private:
        //! map for columns - can be indexed by their name
        std::map<string,COLTYPE> _colmap;

    public:
        //================constructors========================================
        //! default constructor
        table(): _colmap() {}

        //--------------------------------------------------------------------
        //! copy constructor
        table(const table<COLTYPE> &c):_colmap(c._colmap) {}

        //--------------------------------------------------------------------
        //! move constructor
        table(table<COLTYPE> &&c):_colmap(std::move(c._colmap)) {}

        //===================assignment operators=============================
        //! copy assignment operator
        table<COLTYPE> &operator=(const table<COLTYPE> &t)
        {
            if(this == &t) return *this;
            this->_colmap = t._colmap;
            return *this;
        }
        
        //--------------------------------------------------------------------
        //! move assignment operator
        table<COLTYPE> &operator=(table<COLTYPE> &&t)
        {
            if(this == &t) return *this;
            this->_colmap = std::move(t._colmap);
            return *this;
        }

        //===============public member functions==============================
        //! get number of columns
        size_t ncols() const { return _colmap.size(); }

        //--------------------------------------------------------------------
        //! get number of rows
        size_t nrows() const { return _colmap.begin()->second.size(); }

        //--------------------------------------------------------------------
        /*! 
        \brief get keys

        Return a user defined container with the current keys. The container
        must be able to hold string values. 
        \param CTYPE container type
        \return instance of CTYPE with column names
        */
        template<typename CTYPE> CTYPE keys() const
        {
            CTYPE r;
            for(const auto &c:_colmap)
                r.push_back(c.first);

            return r;
        }

        //--------------------------------------------------------------------
        /*!
        \brief get column

        Returns the column that belongs to a particular key. 
        \param key name of the column
        \return const reference to the column
        */
        const COLTYPE &column(const string &key) const
        {
            return _colmap[key];
        }

        //--------------------------------------------------------------------
        const COLTYPE &operator[](const string &key) const 
        {
            return _colmap[key];
        }

        //--------------------------------------------------------------------
        COLTYPE &operator[](const string &key) 
        {
            return _colmap[key];
        }

};
