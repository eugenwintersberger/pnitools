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

#include <boost/tokenizer.hpp>

extern "C" {
#include<readline/readline.h>
#include<readline/history.h>
}

#include "environment.hpp"
#include "interpreter.hpp"
#include "cmd_create.hpp"
#include "cmd_ls.hpp"
#include "cmd_open.hpp"
#include "cmd_cd.hpp"
#include "cmd_mkgrp.hpp"
#include "cmd_mkfield.hpp"
#include "cmd_mkattr.hpp"

//-----------------------------------------------------------------------------
 interpreter::interpreter():
    _current_env(new environment()),
    _cmd_stack()
{
    _cmd_stack["create"] = std::unique_ptr<command>(new cmd_create());
    _cmd_stack["mkgrp"] = std::unique_ptr<command>(new cmd_mkgrp());
    _cmd_stack["ls"] = std::unique_ptr<command>(new cmd_ls());
    _cmd_stack["open"] = std::unique_ptr<command>(new cmd_open());
    _cmd_stack["cd"] = std::unique_ptr<command>(new cmd_cd());
    _cmd_stack["mkfield"] = std::unique_ptr<command>(new cmd_mkfield());
    _cmd_stack["mkattr"] = std::unique_ptr<command>(new cmd_mkattr());
}

//-----------------------------------------------------------------------------
void interpreter::strip_command(const String &s,String
        &cname,std::vector<String> &cargs)
{   
    boost::char_separator<char> separator(" \t\n");
    boost::tokenizer<boost::char_separator<char> > t(s,separator);

    cname = *(t.begin());

    //copy arguments to a vector
    cargs = std::vector<String>();
    for(auto iter = ++t.begin();iter!=t.end();++iter)
        cargs.push_back(*iter);
}

//-----------------------------------------------------------------------------
void interpreter::run()
{
    //interpreter main loop
    while(true)
    {
        //print prompt
        //prompt();

        //read user input
        /*
        std::cin.getline(input_buffer,1024,'\n');
        */
        char *line_buffer = nullptr;
        line_buffer = readline(prompt().c_str());
        String input_str(line_buffer);

        if(line_buffer && *line_buffer)
        {
            add_history(line_buffer);
        }

        //need to free the memory
        free(line_buffer); 
        line_buffer = nullptr;

        //split command name and arguments
        String cname;
        std::vector<String> cargs;
        strip_command(input_str,cname,cargs);

        if(cname == "exit") break;

        //try to grap the command
        if(_cmd_stack.count(cname))
        {
            //execute the command
            try
            {
                _cmd_stack[cname]->setup(cargs);
                _cmd_stack[cname]->execute(_current_env);
            }
            catch(cli_help_request &error)
            {
                std::cout<<"help:"<<std::endl;
                _cmd_stack[cname]->help();
            }
            catch(...)
            {
                std::cout<<"hm - something went wrong!"<<std::endl;
            }
        }
        else
            std::cerr<<"command not found"<<std::endl;

    }
    std::cout<<"Exit interpreter"<<std::endl;
}

//-----------------------------------------------------------------------------
String interpreter::prompt() 
{
    return _current_env->get_current_path()+">> ";
}
