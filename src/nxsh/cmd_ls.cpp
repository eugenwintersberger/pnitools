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

#include "cmd_ls.hpp"
#include <pni/core/config/cli_args.hpp>
#include <pni/core/config/config_parser.hpp>
#include <pni/core/config/configuration.hpp>

#include <boost/tokenizer.hpp>

//-----------------------------------------------------------------------------
cmd_ls::cmd_ls() { }

//-----------------------------------------------------------------------------
void cmd_ls::setup(const std::vector<string> &cargs)
{
    //create configuration setup
    _config = std::unique_ptr<configuration>(new configuration);
    _config->add_option(config_option<bool>("attributes","a",
                                          "show attributes",false));
    _config->add_option(config_option<bool>("long","l",
                                          "show detailed information",false));
    _config->add_argument(config_argument<string>("target",-1,""));

    //parse configuration 
    cli_args args(cargs);
    parse(*_config,args.argc(),args.argv());

    //check if help should be shown
    if(_config->has_option("help"))
        throw cli_help_request(EXCEPTION_RECORD,"show help");
}

//------------------------------------------------------------------------------
void cmd_ls::print_field(const nxfield &f) const
{
    auto s = f.shape<shape_t>();

    std::cout<<"field\t";
    std::cout<<f.name();

    if(_config->value<bool>("long"))
    {
        std::cout<<"\t"<<f.type_id()<<"\t";

        std::cout<<"( ";
        for(auto v: s) std::cout<<v<<" ";

        std::cout<<" )";
    }

    std::cout<<std::endl;
}

//------------------------------------------------------------------------------
void cmd_ls::print_group(const nxgroup &g) const
{
    std::cout<<"group\t";
    std::cout<<g.name();
   
    if(_config->value<bool>("long"))
    {
        if(g.has_attr("NX_class"))
        {
            string attr_str;
            g.attr("NX_class").read(attr_str);
            std::cout<<":"<<attr_str;
        }
    }

    std::cout<<std::endl;

}

//------------------------------------------------------------------------------
void cmd_ls::print_attribute(const nxattribute &a) const
{
    std::cout<<"\tattribute\t"<<a.name();
    if(_config->value<bool>("long"))
    {
        std::cout<<"\t"<<a.type_id()<<"\t";
        std::cout<<"( ";
        auto s = a.shape<shape_t>();
        for(auto v: s) std::cout<<v<<" ";
        std::cout<<")";
    }
    std::cout<<std::endl;
}

//------------------------------------------------------------------------------
void cmd_ls::print_content(const nxgroup &g) const
{
    for(auto o: g)
    {
        if(o.object_type() == pni::io::nx::nxobject_type::NXFIELD)
            print_field(nxfield(o));
        else if(o.object_type() == pni::io::nx::nxobject_type::NXGROUP)
            print_group(nxgroup(o));

        if(_config->value<bool>("attributes"))
        {
            for(auto attr = o.attr_begin();attr!=o.attr_end();++attr)
                print_attribute(*attr);
        }

    }
}

//-----------------------------------------------------------------------------
void cmd_ls::execute(std::unique_ptr<environment> &env)
{
    const nxgroup &cg = env->current_group();

    if(!_config->has_option("target"))
    {
        //just print the content of the current group
        print_content(cg);
    }
    else
    {
        auto target = _config->value<string>("target");
        boost::char_separator<char> separator("/");
        boost::tokenizer<boost::char_separator<char> > t(target,separator);

        nxgroup g(cg);
        for(auto iter = t.begin();iter!=t.end();++iter)
        {
            if(*iter == "..")
                g = g.parent();
            else
            {
                g = g[*iter];
            }
        }
        print_content(g);
    }

}

//-----------------------------------------------------------------------------
void cmd_ls::help() const
{
    std::cout<<*_config<<std::endl;
}


