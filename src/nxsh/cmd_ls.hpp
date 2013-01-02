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

#pragma once

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/config/configuration.hpp>
#include <pni/nx/NX.hpp>

#include "command.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;

/*!
\brief ls command 

Lists the content of a particular group. The group if passed as an argument to
the command. If there is no argument passed to the command the content of the
current group is shown. The command accepts two options: -l (--long) and -a
(--attributes) which are both boolean. The -l option shows additional
information about an object. -a shows attributes attached to the objects along
with the objects.
*/
class cmd_ls : public command
{
    private:
        std::unique_ptr<configuration> _config;

        /*!
        \brief print group content

        Print the content of a group objecct passed to the member function.
        \param g group object 
        */
        void print_content(const NXGroup &g) const;

        //---------------------------------------------------------------------
        /*!
        \brief print field 

        Print a field to std output. 
        \param o field to print
        */
        void print_field(const NXField &o) const;

        //---------------------------------------------------------------------
        /*!
        \brief print gruop

        Print group information to the output. 
        \param o group to print
        */
        void print_group(const NXGroup &o) const;

        //---------------------------------------------------------------------
        /*!
        \brief print attribute information

        Print attribute information to output. 
        \param g attribute to print
        */
        void print_attribute(const NXAttribute &g) const;
    public:
        //! default constructor
        cmd_ls();
        virtual void setup(const std::vector<String> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
        virtual void help() const;
};
