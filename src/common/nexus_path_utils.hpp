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
 * Created on: Jun 27, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <iostream>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxpath.hpp>

using namespace pni::core;
using namespace pni::io::nx;

/*!
\ingroup common_devel
\brief split a nexus path

Splits  a given Nexus path in to two parts at  a particular index s of the group
part of the path.
The best is to have a look at the following example
\code{.cpp}
nxpath path = path_from_string("file.nx:///entry:NXentry/instrument:NXinstrument/data");
nxpath p1,p2;
split_path(path,1,p1,p2);

std::cout<<p1<<std::endl;
std::cout<<p2<<std::endl;

// output
// file.nx:///entry:NXentry
// instrument:NXinstrument/data

\endcode
\param p original path
\param s index where to split 
\param p1 first part of the path
\param p2 second part of the path
*/
void split_path(const nxpath &p,size_t s,nxpath &p1,nxpath &n2);

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief output operator for a nexus path

Prints a nexus path to an output stream. One can either use this to write a
Nexus path to standard out 
\code{.cpp}
nxpath p = ....;
std::cout<<p<<std::endl;
\endcode
or to a string using the stringstream operator
\code{.cpp}
std::stringstream ss;
ss<<p;
\endcode

\param o reference to the output stream
\param p reference to the path
\return reference to the output operator
*/
std::ostream &operator<<(std::ostream &o,const nxpath &p);

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief input operator for a nexus path

Constructing a nexus path from a stream. Analogously to the output operator this
is used to read a path from a stream-able source.
\code{.cpp}
nxpath p;
std::cin>>p;
\endcode

\param i reference to the input stream
\param p reference to the path
\return reference to the advanced original stream
*/
std::istream &operator>>(std::istream &i,nxpath &p);

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief equality operator for two path objects

Compare to path objects. They are considered equal if both paths contain the
same components. 
\param lhs reference to the path on the left handside
\param rhs reference to the path on the right handside
\return true if equal, false otherwise
*/
bool operator==(const nxpath &lhs,const nxpath &rhs);

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief inequality operator for two path objects

Compars two path objects and returns true if they are not equal. 
\param lhs reference to the path on the left handside
\param rhs reference to the path on the right handside
\return true if not equal, false otherwise
*/
bool operator!=(const nxpath &lhs,const nxpath &rhs);
