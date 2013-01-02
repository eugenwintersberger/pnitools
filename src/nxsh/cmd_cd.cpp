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

#include "cmd_cd.hpp"
#include <boost/tokenizer.hpp>

#include <pni/utils/Types.hpp>
#include <pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

//-----------------------------------------------------------------------------
void cmd_cd::setup(const std::vector<String> &cargs)
{
   _target = cargs[0]; 
}

//-----------------------------------------------------------------------------
void cmd_cd::execute(std::unique_ptr<environment> &env)
{
    boost::char_separator<char> separator("/");
    boost::tokenizer<boost::char_separator<char> > t(_target,separator);

    for(auto iter = t.begin();iter!=t.end();++iter)
        env->current_group(*iter);
}
