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
// Created on: Jun 2, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "data_provider.hpp"
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxpath.hpp>

//!
//! \ingroup mcaops_io_devel
//! \brief read MCA data from a Nexus file
//!
//! The provider currently can handle MCA data stored as either a 1 or 2 
//! dimensional field. In the first case only a single spectrum is stored 
//! while in the second case we have several spectra in the file where the
//! first and second dimensions represent the spectrum index and the channel
//! index respectively.
//! 
class nexus_provider : public data_provider
{
    private:
        typedef operation::array_type array_type;
    
        pni::io::nx::h5::nxfile _file;
        pni::io::nx::h5::nxfield _mca_field;
        pni::io::nx::h5::nxfield _channel_field;

        array_type _channel_cache;
        size_t _spectrum_index;
    public:
        //!
        //! \throws shape_mismatch_error if MCA data rank is higher than 2
        nexus_provider(const pni::core::string &file_name,
                       const pni::core::string &channel_path,
                       const pni::core::string &mca_path,
                       size_t channel_offset);

        ~nexus_provider();

        virtual bool finished() const;

        virtual value_type next();
};
