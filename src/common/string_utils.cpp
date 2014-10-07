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
// Created on: Oct 18, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <cctype>
#include "string_utils.hpp"

//-----------------------------------------------------------------------------
string trim(const string &s)
{
    size_t start_index = 0;
    for(auto iter = s.begin();iter!=s.end();++iter)
    {
        if((*iter == ' ')||(*iter=='\n')||(*iter=='\t')) 
        {
            start_index++;
            continue;
        }
        else break;
    }

    size_t stop_index = 0;
    for(auto iter = s.rbegin();iter!=s.rend();++iter)
    {
        if((*iter == ' ')||(*iter=='\n')||(*iter=='\t'))
        {
            stop_index++;
            continue;
        }
        else break;
    }

    return string(s,start_index,(s.size()-stop_index-start_index));
}

//----------------------------------------------------------------------------
string to_lower(const string &s)
{
    string l(s);
    std::transform(s.begin(),s.end(),l.begin(),::tolower);
    return l;
}

//----------------------------------------------------------------------------
string to_upper(const string &s)
{
    string u(s);
    
    std::transform(s.begin(),s.end(),u.begin(),::toupper);
    return u;
}

