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

#include <list>
#include <h5cpp/hdf5.hpp>


//!
//! @ingroup nxls_devel
//! @brief list of links obtained from the tree
//!
class LinkList : public std::list<hdf5::node::Link>
{
  public:
    using std::list<hdf5::node::Link>::list;

    template<typename IterT> static LinkList create(IterT begin,IterT end);
};

template<typename IterT>
LinkList LinkList::create(IterT begin,IterT end)
{
  LinkList list;
  std::copy(begin,end,std::back_inserter(list));
  return list;
}


