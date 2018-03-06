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

#include "link_metadata.hpp"

using namespace pni::io;

nexus::Path get_path_from_link(const hdf5::node::Link &link)
{
  hdf5::node::Group parent = link.parent();
  nexus::Path path = nexus::get_path(parent);
  path.push_back({link.path().name(),""});

  return path;
}

LinkMetadata::LinkMetadata(const hdf5::node::Link &link):
  Metadata(get_path_from_link(link)),
  type_(link.type()),
  target_(link.target()),
  status_(link.is_resolvable())
{}

hdf5::node::LinkType LinkMetadata::link_type() const noexcept
{
  return type_;
}

hdf5::node::LinkTarget LinkMetadata::link_target() const noexcept
{
  return target_;
}

bool LinkMetadata::status() const noexcept
{
  return status_;
}

Metadata::Type LinkMetadata::type() const
{
  return Metadata::Type::LINK;
}






