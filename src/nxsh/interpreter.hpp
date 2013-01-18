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

#include <iostream>
#include <map>
#include <vector>
#include <pni/core/Types.hpp>
#include <pni/io/nx/NX.hpp>

#include "environment.hpp"
#include "command.hpp"

using namespace pni::core;
using namespace pni::io::nx::h5;

/*!
\brief interpreter for nexus shell

The interpreter class for the Nexus shell. This class implements the main-loop
of the interpreter. 
*/
class interpreter
{
    private:
        //! pointer to the current working environment
        std::unique_ptr<environment> _current_env;
        //! command stack
        std::map<String,std::unique_ptr<command> > _cmd_stack;

        /*!
        \brief strip command

        This private member function strips the command from the user input and 
        returns the name of the command along with a vector with the command
        line options passed to the command.
        \param s user CLI input
        \param cname command name
        \param cargs command options and arguments
        */
        void strip_command(const String &s,String &cname,
                           std::vector<String> &cargs);
    public:
        //---------------------------------------------------------------------
        //!default constructor
        interpreter(); 

        //---------------------------------------------------------------------
        //! run mainloop
        void run();
        
        //---------------------------------------------------------------------
        //! return prompt string
        String prompt() ;

};
