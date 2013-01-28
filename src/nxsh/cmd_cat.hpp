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
 * Created on: Jan 04, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <pni/core/config/configuration.hpp>
#include "command.hpp"
#include <pni/io/nx/nx.hpp>

using namespace pni::io::nx::h5;
using namespace pni::core;

//! create something
class cmd_cat : public command
{
    private:
        std::unique_ptr<configuration> _config;

        template<typename T>
        void print_field(const nxfield &f) const;
    public:
        virtual void setup(const std::vector<string> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
        virtual void help() const;
};

//-----------------------------------------------------------------------------
template<typename T> void cmd_cat::print_field(const nxfield &f) const
{
    //get the field shape
    auto s = f.shape<shape_t>();
    darray<T> data(s);

    f.read(data);

    for(auto v: data) std::cout<<v<<" ";
    std::cout<<std::endl;

}
