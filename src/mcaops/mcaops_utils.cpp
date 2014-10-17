//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//************************************************************************
// Created on: May 10,2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "mcaops.hpp"

//-----------------------------------------------------------------------------
configuration create_global_config()
{
    configuration config;

    //----------------setting up the program options---------------------------
    //these options do not show up in the help text
    config.add_argument(config_argument<string>("command",1));
    config.add_argument(config_argument<string>("input",2));

    //-------------------------------------------------------------------------
    //global options valid for all commands
    config.add_option(config_option<bool>("help","h","show help text",false));
    config.add_option(config_option<bool>("verbose","v","show verbose output",
                                          false));
    config.add_option(config_option<bool>(
                "header","","write headers before output",false));
    config.add_option(config_option<string>("xcolumn","",
                "name of the column with bin center values",""));
    config.add_option(config_option<string>("ycolumn","",
                "name of the column with actual MCA data",""));

    return config;
}

//-----------------------------------------------------------------------------
configuration create_rebin_config()
{
    configuration config;
    config.add_option(config_option<size_t>("binsize","b",
                "number of bins to collate",1));
    config.add_option(config_option<bool>("noxrebin","",
                "do not rebin the x-axis, use simple indices instead",false));
    config.add_option(config_option<bool>("normalize","",
                "normalize the rebinned data",false));

    return config;
}

//-----------------------------------------------------------------------------
configuration create_scale_config()
{
    configuration config;
    config.add_option(config_option<size_t>("center","c",
                "index of center bin"));
    config.add_option(config_option<float64>("delta","d",
                "size of a bin"));
    config.add_option(config_option<float64>("cvalue","x",
                "position of the center bin"));

    return config;
}

//-----------------------------------------------------------------------------
op_ptr select_operator(const configuration &config,
                       const configuration &cmd_config)
{
    string command = config.value<string>("command");

    if(command == "max") 
        return op_ptr(new max_operation());

    if(command == "sum")
        return op_ptr(new sum_operation());

    if(command == "dump")
        return op_ptr(new dump_operation());

    if(command == "rebin")
    {
        rebin_operation *op = new rebin_operation();

        if(cmd_config.has_option("binsize"))
            op->bin_size(cmd_config.value<size_t>("binsize"));

        //switch of rebinning of the x-axis
        if(cmd_config.has_option("noxrebin"))
            op->no_x_rebinning(cmd_config.value<bool>("noxrebin"));

        if(cmd_config.has_option("normalize"))
            op->normalization(cmd_config.value<bool>("normalize"));

        return op_ptr(op);
    }

    if(command == "scale")
    {
        scale_operation *op = new scale_operation();
        if(cmd_config.has_option("center"))
        {
            op->center_bin(cmd_config.value<size_t>("center"));
            op->use_data_maximum(false);
        }
        else 
            op->use_data_maximum(true);

        if(cmd_config.has_option("delta"))
            op->delta(cmd_config.value<float64>("delta"));

        if(cmd_config.has_option("cvalue"))
            op->center_value(cmd_config.value<float64>("cvalue"));

        return op_ptr(op);
    }

    std::cerr<<"Unkown MCA operation - see manpage"<<std::endl;

    //better throw an exception here
    return op_ptr(nullptr);
}


