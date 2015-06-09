//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// pnitools is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pnitools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
// Created on: Jun 9, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "options_splitter.hpp"

using namespace pni::core;

//----------------------------------------------------------------------------
options_splitter::options_splitter(const args_vector &keywords):
    _keywords(keywords)
{}

//----------------------------------------------------------------------------
args_map options_splitter::operator()(const args_vector &args)
{
    
    string current_key = "global"; 

    //return an empty map if no arguments are passed
    if(args.empty()) 
        return args_map{{current_key,args_vector()}};

    //if no keyworeds where passed during construction
    if(_keywords.empty()) 
        return args_map{{current_key,args}};


    //here we have to do some work
    args_map m;
    args_vector local_args;
    for(auto arg: args)
    {
        if(std::find(_keywords.begin(),_keywords.end(),arg)!=_keywords.end())
        {
            m.insert({current_key,local_args});
            local_args  = args_vector();
            current_key = arg;
        }
        else
            local_args.push_back(arg);
    }
    //we need to insert the last vector
    m.insert({current_key,local_args});

    return m;

}
