/*
 * ProgramConfig.cpp
 *
 *  Created on: May 31, 2011
 *      Author: eugen
 */

#include<string>
#include<vector>
#include<cstdio>
#include<cstdlib>

#include "ProgramConfig.hpp"

//-----------------------------------------------------------------------------
std::ostream &ProgramConfig::print(std::ostream &o) const
{
    return o<<_visible_opts;
}

//-----------------------------------------------------------------------------
ProgramConfig::ProgramConfig():
    _vmap(popts::variables_map()),
    _visible_opts(popts::options_description()),
    _hidden_opts(popts::options_description()),
    _oargs(popts::positional_options_description())
{
	//set command line options
	_visible_opts.add_options()
			("help,h","print help message")
			;
}


//----------------------------------------------------------------------------
void ProgramConfig::parse(int argc,char **argv)
{
    //merging hidden and visible options to a single option description
    popts::options_description total_opts;
    total_opts.add(_visible_opts);
    total_opts.add(_hidden_opts);

    //run the parser
	popts::store(popts::command_line_parser(argc,argv).
                 options(total_opts).
                 positional(_oargs).run(),
                 _vmap);

    //notify the variable map that we are done
	popts::notify(_vmap);
    
    if(has_option("help"))
        throw CLIHelpRequest(EXCEPTION_RECORD,"help was requested!");
}

//-----------------------------------------------------------------------------
bool ProgramConfig::has_option(const String &name) const
{
    if(_vmap.count(name)) return true;
    return false;
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const ProgramConfig &c)
{
    return c.print(o);
}


