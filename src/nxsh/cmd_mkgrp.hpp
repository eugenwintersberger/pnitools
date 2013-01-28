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
 * Created on: Jan 02, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/config/configuration.hpp>
#include "command.hpp"

/*!
\brief create a group

Create a group. The command takes one argument: the group to create. 
The only option allowed is -c (--class) a string determining the class of the
group. 
*/
class cmd_mkgrp : public command
{
    private:
        std::unique_ptr<configuration> _config;
    public:
        virtual void setup(const std::vector<string> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
        virtual void help() const;
};


