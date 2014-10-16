//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jun 5,2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "det2nx.hpp"
#include <pni/io/cbf/cbf_reader.hpp>
#include <pni/io/tiff/tiff_reader.hpp>
#include "../common/file_utils.hpp"
//#include "../common/nexus_field_utils.hpp"

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif


template<typename ...ARGST>
h5::nxobject create_field(const h5::nxobject &root,
                          const nxpath &path,type_id_t tid,ARGST ...args)
{
    if(tid == type_id_t::UINT8)
        return create_field<uint8>(root,path,args...);
    else if(tid == type_id_t::INT8)
        return create_field<int8>(root,path,args...);
    if(tid == type_id_t::UINT16)
        return create_field<uint16>(root,path,args...);
    else if(tid == type_id_t::INT16)
        return create_field<int16>(root,path,args...);
    if(tid == type_id_t::UINT32)
        return create_field<uint32>(root,path,args...);
    else if(tid == type_id_t::INT32)
        return create_field<int32>(root,path,args...);
    if(tid == type_id_t::UINT64)
        return create_field<uint64>(root,path,args...);
    else if(tid == type_id_t::INT64)
        return create_field<int64>(root,path,args...);

    return h5::nxobject();
}

//-----------------------------------------------------------------------------
h5::nxobject get_field(const h5::nxobject &root,
                       const pni::io::image_info &info,
                       const nxpath &path,size_t deflate) 
{
    h5::nxobject field;
    h5::nxdeflate_filter filter(deflate,true);


    try
    {
        field = get_object(root,path);
    }
    catch(pni::core::index_error &error)
    {
        std::cerr<<error<<std::endl;
    }
    catch(...)
    {
        //if something went wrong we can first assume that the field does not
        //exist
        shape_t shape({0,info.nx(),info.ny()});
        shape_t chunk_shape({1,info.nx(),info.ny()});

        if(deflate)
            field = create_field(root,path,info.get_channel(0).type_id(),
                                 shape,chunk_shape,filter);
        else
            field = create_field(root,path,info.get_channel(0).type_id(),
                                 shape,chunk_shape);
    }

    return field;
}
