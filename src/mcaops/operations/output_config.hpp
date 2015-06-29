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
// Created on: Jun 29,2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>


//!
//! \ingroup mcaops_devel
//! \brief configuration for operation output
//!
//! This class stores the configuration information for the program output. 
//! 
class output_config
{
    private:
        //! true if the channel output should be shown
        bool _channel_output;
        //! separator character for channels (\n by default)
        pni::core::string _channel_separator;
    public:
        //! default constructor
        output_config();

        //--------------------------------------------------------------------
        //! constructor
        output_config(bool channel_output,pni::core::string channel_separator);

        //--------------------------------------------------------------------
        //! copy constructor
        output_config(const output_config &c);

        //--------------------------------------------------------------------
        //! 
        //! \brief set channel output
        //!
        //! Returns true if the channel/bin data should be added 
        //! to the. 
        bool channel_output() const;

        //--------------------------------------------------------------------
        //!
        //! \brief get channel separator
        //!
        //! Returns the character for channel separation. By default 
        //! this is a carrige return. 
        //!
        pni::core::string channel_separator() const;
};
