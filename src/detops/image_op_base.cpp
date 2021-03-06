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
 * Created on: Nov 14, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "image_op_base.hpp"

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

std::ostream &operator<<(std::ostream &stream,const image_op_base &op)
{
    const image_type &result = op.result();

#ifdef NOFOREACH
    BOOST_FOREACH(auto r,result)
#else
    for(auto r: result)
#endif
        stream<<r;
    return stream;
}
