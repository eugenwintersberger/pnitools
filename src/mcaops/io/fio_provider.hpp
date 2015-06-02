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
// Created on: May 29, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "data_provider.hpp"
#include <pni/io/fio/fio_reader.hpp>

//!
//! \ingroup mcaops_io_devel
//! \brief read MCA data from a FIO file
//! 
//! This provider reads MCA data from a FIO file. As FIO files can store
//! several columns of data the user must provide at least the name of the 
//! column from which to read the MCA data. So the -m option is mandatory 
//! when using FIO files. If no column with the channel or bin-center data
//! is provided the channel index will be computed automatically. 
//! If the user also provides the name of the column with the bin or 
//! channel index data this data will be used instread.
//!
class fio_provider : public data_provider
{
    private:
        //some private data types
        typedef operation::array_type array_type;
        typedef std::vector<pni::core::float64> vector_type;

        //! stores the name of the file from which to read
        pni::core::string _filename;
        //! column name from which to read MCA data
        pni::core::string _mca_column;
        //! column name from which to read channel/center bin data
        pni::core::string _channel_column;
        //! flag indicating whether or not a file has been read
        bool _file_read;
        
        //!
        //! \brief read mca data
        //! 
        //! \throws io_error in case of any IO error
        //! \param reader reference to the reader instance
        //! \return array with MCA data
        //!
        array_type get_mca_data(const pni::io::fio_reader &reader) const;

        //--------------------------------------------------------------------
        //!
        //! \brief get channel data
        //!
        //! The last argument is the number of channels. This value has to be
        //! provided for situations where no channel column is provided by the 
        //! user.
        //! 
        //! \throws io_error in case of errors
        //! \param reader reference to the reader instance
        //! \param n number of channels
        //! \return channel/center-bin data
        //! 
        array_type get_channel_data(const pni::io::fio_reader &reader,
                                    size_t n) const;

    public:
        //! 
        //! \brief constructor
        //!
        //! \throws key_error if no MCA column name has been provided
        //! 
        //! \param filename the name of the file from which to read data
        //! \param mca_column_name column name for MCA data
        //! \param channel_column_name column name for channel/center-bin data
        //!
        fio_provider(const pni::core::string &filename,
                     const pni::core::string &mca_column_name,
                     const pni::core::string &channel_column_name="");

        //--------------------------------------------------------------------
        //! destructor
        ~fio_provider();

        //--------------------------------------------------------------------
        //!
        //! \brief true if finished
        //!
        //! \return true if data has been delivered 
        //!
        virtual bool finished() const;

        //--------------------------------------------------------------------
        //!
        //! \brief next dataset
        //! 
        //! \throws io_error in case of any IO error
        //!
        //! \return return the next dataset
        //!
        virtual value_type next();
};
