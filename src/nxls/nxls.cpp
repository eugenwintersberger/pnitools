//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: 30.06.2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "config.hpp"
#include "utils.hpp"
#include <iostream>
#include <sstream>
#include <pni/core/types.hpp>
#include <pni/core/configuration.hpp>
#include <pni/io/nexus.hpp>
#include "metadata.hpp"
#include "metadata_extractor.hpp"
#include "output_configuration.hpp"
#include "output_records.hpp"
#include "record_builder.hpp"
#include "column_widths.hpp"



//setting namespaces
using namespace pni::io;
using namespace pni::core;


//!
//! \ingroup nxls_devel
//! \brief main program
//! 
//! The main program sequence of nxls.
//!
int main(int argc,char **argv)
{
  hdf5::error::Singleton::instance().auto_print(false);

  //create configuration
  configuration config = get_config(argc,argv);

  // obtain the path from the program configuration
  nexus::Path base_path = get_base_path(config);

  // get the file
  hdf5::file::File file = get_file(base_path);

  // get the base object
  nexus::PathObject base;
  try
  {
    base = get_base(file,base_path);
  }
  catch(const std::runtime_error &error)
  {
    std::cerr<<error.what()<<std::endl;
    return 1;
  }

  //
  // we need some special treatment if the base object is a dataset or an
  // attribute. These objects do not have children und are thus simply
  // displayed.
  //
  MetadataList metadata;
  MetadataExtractor extractor(metadata,config.value<bool>("show-attributes"));
  if(nexus::is_dataset(base))
  {
    hdf5::node::Dataset dataset = base;
    extractor(dataset);
  }
  else if(nexus::is_attribute(base))
  {
    extractor(hdf5::attribute::Attribute(base));
  }
  else if(nexus::is_group(base))
  {
    hdf5::node::Group base_group = base;

    if(config.value<bool>("recursive"))
    {
      auto begin = hdf5::node::RecursiveLinkIterator::begin(base_group);
      auto end   = hdf5::node::RecursiveLinkIterator::end(base_group);
      std::for_each(begin,end,extractor);
    }
    else
    {
      std::for_each(base_group.links.begin(),base_group.links.end(),
                     extractor);
    }
  }

  OutputConfiguration output_config(config.value<bool>("long"),
                                    config.value<bool>("full-path"),
                                    base_path);

  RecordBuilder record_builder(output_config);
  OutputRecords records;
  std::transform(metadata.begin(),metadata.end(),
                 std::back_inserter(records),record_builder);

  ColumnWidths max_col_widths(records.front().column_widths());
  for(auto record: records)
  {
    ColumnWidths widths = record.column_widths();
    std::transform(widths.begin(),widths.end(),max_col_widths.begin(),max_col_widths.begin(),
                   [](size_t w,size_t max_w)
                   {
                    return w>max_w ? w : max_w;
                   });
  }

  for(auto record: records)
  {
    auto witer = max_col_widths.begin();
    std::for_each(record.begin(),record.end(),
                    [&witer](const std::string &column)
                    { std::cout<<std::left<<std::setw((*witer++)+3)<<column;});

    std::cout<<std::endl;
  }


  return 0;
}
