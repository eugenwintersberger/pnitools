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
// Created on: Mar 6, 2018
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "output_configuration.hpp"


OutputConfiguration::OutputConfiguration(bool long_output,bool full_path,
                                 const pni::io::nexus::Path &base_path):
  long_output_(long_output),
  full_path_(full_path),
  base_path_(base_path)
{}

bool OutputConfiguration::show_full_path() const noexcept
{
  return full_path_;
}

bool OutputConfiguration::show_long_output() const noexcept
{
  return long_output_;
}

const pni::io::nexus::Path &OutputConfiguration::base_path() const noexcept
{
  return base_path_;
}



