//
// (c) Copyright 2018 DESY
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
// Created on: Feb 28, 2018
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "metadata.hpp"
#include "link_list.hpp"

//!
//! @ingroup nxls_devel
//! @brief extract metadata from a list of links
//!
//! The class stores a reference to a metadata list and appends items to it
//! from a list of links. Subsequent calls to this class append more metadata.
//!
class MetadataExtractor
{
  private:
    MetadataList &metadata_;
    bool with_attributes_;

    //!
    //! @brief extract attribute metadata from a node
    //!
    //! This private utility method extracts attribute metadata from a
    //! given node and appends it to the metadata list.
    //!
    //! @param node reference to the node from which to extract metadata
    //!
    void process_attributes(const hdf5::node::Node &node);
  public:

    //!
    //! @brief constructor
    //!
    //!
    explicit MetadataExtractor(MetadataList &metadata, bool with_attributes);

    //!
    //! @brief extract metadata from a node
    //!
    void operator()(const hdf5::node::Node &node);

    //!
    //! @brief extract metadata from a single attribute
    //!
    void operator()(const hdf5::attribute::Attribute &attribute);

    //!
    //! @brief extract metadata from a link
    //!
    //! If the link cannot be resolved the metadata for the link itself is
    //! stored. Otherwise the link will be resolved and the metadata for the
    //! object referenced by the link is stored.
    //!
    void operator()(const hdf5::node::Link &link);


};
