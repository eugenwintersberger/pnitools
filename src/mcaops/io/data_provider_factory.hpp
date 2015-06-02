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
// Created on: May 12,2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/configuration/configuration.hpp>
#include "data_provider.hpp"

//!
//! \ingroup mcaops_io_devel 
//! \brief data provider factory
//! 
//! This factory class returns a smart pointer to a particular data provider
//! implementation. Which provider to load depends on the user configuration 
//! passed to the program via the command line. 
//!
class data_provider_factory
{
    private:
        //! a string vector for filenames
        typedef std::vector<pni::core::string> filename_vector;
        //! provider pointer type
        typedef data_provider::pointer_type pointer_type;

        //!
        //! \brief create standard in provider
        //!
        //! Utility function used internaly by the factory to create a 
        //! standard input provider. 
        //!
        //! \param c reference to the global program configuration
        //! \return smart pointer to the provider implementation
        //!
        static pointer_type 
            create_stdin_provider(const pni::core::configuration &c);

        //!
        //! \brief create FIO provider
        //!
        //! Utility function used to create a FIO provider. 
        //!
        //! \param c reference to the global program configuration
        //! \return smart pointer to the provider instance
        static pointer_type
            create_fio_provider(const pni::core::configuration &c,
                                const filename_vector &filenames);
    public:
        //!
        //! \brief create provider instance
        //! 
        //! Returns a smart pointer to a data provider implementation. The type 
        //! of provider is determined by the global program configuration passed 
        //! via the command line. 
        //! \li if no input files are provided the standard input provider will
        //!     be generated
        //! \li if there are input files, the first of them determines the file 
        //!     type, and a file provider according to this type will be 
        //!     created.
        //! 
        static pointer_type 
            create(const pni::core::configuration &config);
};
