/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * pnitools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pnitools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Dec 18, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "file_list.hpp"
#include <boost/format.hpp>



//-----------------------------------------------------------------------------
bool file_list::_fill_from_num_range(const String &p)
{

    nrseparator sep(":");
    nrtokenizer token(p,sep);
    size_t start = 0;
    size_t stop = 0;
    size_t stride = 1;
    String p_template;

    size_t index = 0;
    for(auto iter = token.begin(); iter!= token.end();++iter)
    {
        std::stringstream ss(*iter);
        switch(index)
        {
            case 0: ss>>p_template; break;
            case 1: ss>>start; break;
            case 2: ss>>stop; break;
            case 3: ss>>stride; break;
        }
        index++;
    }

    if(index<2) return false;

    index = start;
    do
    {
        std::stringstream ss;
        ss<<boost::format(p_template)%index;
        _file_list.push_back(ss.str());
        index += stride;

    }while(index<=stop);
    
    

    return true;

}
        
