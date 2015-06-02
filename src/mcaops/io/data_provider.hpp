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
#include "../operations/operation.hpp"

//!
//! \ingroup mcaops_io_devel
//! \brief data provider base class
//!
//! Base class for all data providers. This class defines the interface every 
//! data provider class has to satisfy. Along with the interface it also 
//! determines a set of datatypes used for reading data.
//! 
//! Every data provider somehow acts like a container. Every element is a 
//! pair of channel and MCA data. Concerning memory, one such pair must 
//! fit into memory. 
//!
class data_provider
{
    private:
        //! 
        //! \brief local index generator
        //!
        //! This index generator is used when no index or bin-center 
        //! column is provided by the user. This data member is used as a
        //! prototype. Whenever a concrete provider requests an index generator
        //! a new instance, based on this very instance, will be created.
        //!
        index_generator _index_gen;
    public:
        //!
        //! \brief pointer type
        //!
        //! Shared pointer type for data providers. Only used for 
        //! polymorphy.
        //! 
        typedef std::unique_ptr<data_provider> pointer_type;

        //--------------------------------------------------------------------
        //!
        //! \brief array type
        //! 
        //! Array type used to store data in memory.
        //! 
        typedef operation::array_type array_type;
        
        //--------------------------------------------------------------------
        //!
        //! \brief element type 
        //!
        //! Pair of channel and MCA data. 
        //! 
        typedef std::pair<array_type,array_type> value_type;

        //--------------------------------------------------------------------
        //! default constructor
        data_provider();

        //--------------------------------------------------------------------
        //!
        //! \brief constructor
        //! 
        //! Take an index generator as its only argument. 
        //!
        data_provider(const index_generator &g);

        //--------------------------------------------------------------------
        //! destructor
        virtual ~data_provider();


        //--------------------------------------------------------------------
        //!
        //! \brief returns provider status
        //!
        //! This abstract method must be implemented by every concrete 
        //! provider. It returns true if the last channel/MCA pair has 
        //! been delivered. 
        //!
        //! \return true if done
        virtual bool finished() const = 0;

        //--------------------------------------------------------------------
        //!
        //! \brief return next dataset
        //!
        //! Returns the next channel/MCA pair to the calling application. 
        //!
        //! \return channel/MCA pair
        //!
        virtual value_type next()  = 0;

        //---------------------------------------------------------------------
        //!
        //! \brief create index generator
        //!
        //! Creates a new index generator based on the prototype stored 
        //! as a member variable.
        //! 
        //! \return new instance of index_generator.
        index_generator create_generator() const;


    
};
