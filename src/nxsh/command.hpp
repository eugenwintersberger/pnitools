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

#include "environment.hpp"

/*!
\brief base class for shell commands

This is the base class for all commands available for the command shell. This
class provides a purely virtual interface. All command classes must implement
this interface.
*/
class command
{
    public:
        /*!
        \brief setup the command

        Each command requires setup before execution which is done by this
        member function. The configuration comes from the command line options
        passed by the user. Options and arguments on the command line are
        separated by whitespace-characters. It is the job of the interpreter to
        split this string into a vector of strings which is passed as an
        argument to this function. 

        If the user passes the -h or --help command line option a
        cli_help_request exception is thrown indicating that a help message
        shall be shown on the terminal.
        \throws cli_help_request if the user requests help
        \param cargs command line arguments and options in a vector
        */
        virtual void setup(const std::vector<String> &cargs) = 0;

        //---------------------------------------------------------------------
        /*!
        \brief execute the command
        
        This member function executes the command. The only argument taken is
        the current interpreter environment. 
        \param current environment of the shell.
        */
        virtual void execute(std::unique_ptr<environment> &env) = 0;       

        //---------------------------------------------------------------------
        /*!
        \brief print help message

        Print the help message for the command. This member function will be
        called by the interpreter if a cli_help_request exception is thrown by
        the setup method.
        */
        virtual void help() const = 0;
};

    


