//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// pnitools is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pnitools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
// Created on: Oct 13,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include "output_config.hpp"

using namespace pni::core;
using namespace pni::io::nx;

//!
//! \ingroup nxls_devel
//! \brief return metadata
//! 
//! Return a string with metadata for an object. 
//! 
//! \param o reference to the object
//! \return string with metadata
//! 
string get_metadata(const h5::nxobject &o);

//----------------------------------------------------------------------------
//! 
//! \ingroup nxls_devel
//! \brief get field metadata
//! 
//! Return a string with metadata for a field. 
//! 
//! \param o field instance
//! \return string with metadata
//!
string get_field_metadata(const h5::nxobject &o);

//----------------------------------------------------------------------------
//!
//! \ingroup nxls_devel
//! \brief get group metadata 
//!
//! Return a string with metadata for a group. 
//!
//! \param o group instance
//! \return string with metadata
//!
string get_group_metadata(const h5::nxobject &o);

//----------------------------------------------------------------------------
//!
//! \ingroup nxls_devel
//! \brief get attribute metadata
//!
//! Return a string with metadata for an attribute.
//!
//! \param o attribute instance
//! \return string with metadata
//!
string get_attribute_metadata(const h5::nxobject &o);

//----------------------------------------------------------------------------
//!
//! \ingroup nxls_devel
//! \brief get content metadata 
//!
//! This function returns a string with metadata for data holding objects. 
//! These are attributes and fields. It is used by get_field_metadata and 
//! get_attribute_metadata to obtain the datatype and the shape of the 
//! field or attribute.
//!
//! \param o attribute or field instance
//! \return string with metadata
//!
string get_data_metadata(const h5::nxobject &o);

//----------------------------------------------------------------------------
//!
//! \ingroup nxls_devel
//! \brief producing nxls output
//! 
//! This class produces the output of nxls. 
//!
class output
{
    private:
        //! output stream for nxls
        std::ostream &_stream;
        //! the output configuration
        output_config _config;

        //--------------------------------------------------------------------
        //!
        //! \brief produce attribute output
        //! 
        //! This is function template writes attribute data to the output 
        //! stream. 
        //! 
        //! \tparam OTYPE object type
        //! \param parent instance of OTYPE with attributes
        //! 
        template<typename OTYPE> void attribute_output(const OTYPE &parent);

        //--------------------------------------------------------------------
        //!
        //! \brief get path
        //!
        //! This function returns the string representation of the path of 
        //! an object. Besides this it also removes the root part of the 
        //! path unless the -l option is set. 
        //!
        //! \param o nexus object
        //! \return string representation of the objects path
        //!
        string get_path(const h5::nxobject &o) const;

        

    public:
        //!
        //! \brief constructor
        //!
        //! \param stream the desired output stream
        //! \param config configuration instance 
        //!
        explicit output(std::ostream &stream,
                        const output_config &config);
   
        //--------------------------------------------------------------------
        //!
        //! \brief perform output operation
        //!
        //! The () operator of this class finally writes the desired output to 
        //! a stream. 
        //! 
        //! \tparam OTYPE parent object type
        //! \param parent the root object over which to iterate
        //! 
        template<typename OTYPE> void operator()(const OTYPE &parent);

        void write_object(const h5::nxobject &o);

            

};


//----------------------------------------------------------------------------
template<typename OTYPE>
void output::attribute_output(const OTYPE &parent)
{
    //iterate over all attributes
    for(auto attribute: parent.attributes)
    {
        write_object(attribute);
    }
}

//----------------------------------------------------------------------------
template<typename OTYPE>
void output::operator()(const OTYPE &parent)
{
    // iterate over all children of the parent object
    for(auto child: parent) write_object(child);
}
