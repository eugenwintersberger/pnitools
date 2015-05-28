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

#include "data_provider.hpp"

//!
//! \ingroup mcaops_devel
//! \brief standard input data provider
//! 
//! This data provider reads channel/MCA data from standard input. If default
//! constructed all data until EOF is considered as a single channel/MCA pair. 
//! If an MCA size is provided during construction, the data read from 
//! standard input is subdivided into several blocks with mca_size entries. 
//! 
class stdin_provider : public data_provider
{
    private:
        //! number of channels for a single MCA
        size_t _mca_size;
    public:
        //! 
        //! \brief constructor
        //!
        //! The mca_size argument determines the number of channels for a 
        //! single MCA spectrum and the index generator is used to 
        //! generate channel indices if not provided by the input data. 
        //! 
        //! \param mca_size number of channels for each MCA spectrum
        //! \param g the index generator to use
        //!
        stdin_provider(size_t mca_size,const index_generator &g);

        //--------------------------------------------------------------------
        //!
        //! \brief constructor
        //! 
        //! Only with mca_size. 
        //!
        //! \param mca_size number of channels per spectrum
        //! 
        stdin_provider(size_t mca_size);

        //--------------------------------------------------------------------
        //! destructor
        ~stdin_provider();

        //--------------------------------------------------------------------
        //!
        //! \brief true if finished
        //!
        //! \return true if stream is EOF
        //!
        virtual bool finished() const;

        //--------------------------------------------------------------------
        //!
        //! \brief next dataset
        //! 
        //! \return return the next dataset
        //!
        virtual value_type next();
};
