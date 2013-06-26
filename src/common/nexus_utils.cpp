/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: Jun 26, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "nexus_utils.hpp"


void split_path(const nxpath &p,size_t s,nxpath &p1,nxpath &p2)
{
    
    auto split_iter = p.begin();
    std::advance(split_iter,s);

    nxpath::group_path_t gp1(s),gp2(p.size()-s);
    std::copy(p.begin(),split_iter,gp1.begin());
    std::copy(split_iter,p.end(),gp2.begin());

    p1 = nxpath(p.filename(),gp1,"");
    p2 = nxpath("",gp2,p2.attribute());
}
