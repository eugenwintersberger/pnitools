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


#include "metadata_extractor.hpp"
#include "link_metadata.hpp"
#include "group_metadata.hpp"
#include "attribute_metadata.hpp"
#include "dataset_metadata.hpp"

MetadataExtractor::MetadataExtractor(MetadataList &metadata,bool with_attributes):
  metadata_(metadata),
  with_attributes_(with_attributes)
{}

void MetadataExtractor::operator()(const hdf5::node::Node &node)
{
  if(node.type() == hdf5::node::Type::GROUP)
    metadata_.push_back(Metadata::UniquePointer(new GroupMetadata(hdf5::node::Group(node))));
  else if(node.type() == hdf5::node::Type::DATASET)
    metadata_.push_back(Metadata::UniquePointer(new DatasetMetadata(hdf5::node::Dataset(node))));

  if(with_attributes_)
    std::for_each(node.attributes.begin(),node.attributes.end(),*this);
}

void MetadataExtractor::operator()(const hdf5::attribute::Attribute &attribute)
{
  metadata_.push_back(Metadata::UniquePointer(new AttributeMetadata(attribute)));
}

void MetadataExtractor::operator()(const hdf5::node::Link &link)
{
  if(!link.is_resolvable())
  {
    //
    // if the link is not resolvable we just return the link
    //
    metadata_.push_back(Metadata::UniquePointer(new LinkMetadata(link)));
  }
  else
  {
    //
    // if the link can be resolved we have a look on the node it refers to
    //
    this->operator()(*link);
  }
}





