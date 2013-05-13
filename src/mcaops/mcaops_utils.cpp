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
 * Created on: May 10,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "mcaops.hpp"

//-----------------------------------------------------------------------------
op_ptr select_operator(const configuration &config,
                       const configuration &scale_config,
                       const configuration &rebin_config) 
{
    string command = config.value<string>("command");

    if(command == "max") 
        return op_ptr(new max_operation());

    if(command == "sum")
        return op_ptr(new sum_operation());

    if(command == "rebin")
    {
        rebin_operation *op = new rebin_operation();

        if(rebin_config.has_option("binsize"))
            op->bin_size(rebin_config.value<size_t>("binsize"));

        //switch of rebinning of the x-axis
        if(rebin_config.has_option("noxrebin"))
            op->no_x_rebinning(rebin_config.value<bool>("noxrebin"));

        return op_ptr(op);
    }

    if(command == "scale")
    {
        scale_operation *op = new scale_operation();
        if(scale_config.has_option("center"))
        {
            op->center_bin(scale_config.value<size_t>("center"));
            op->use_data_maximum(false);
        }
        else 
            op->use_data_maximum(true);

        if(scale_config.has_option("delta"))
            op->delta(scale_config.value<float64>("delta"));

        if(scale_config.has_option("cvalue"))
            op->center_value(scale_config.value<float64>("cvalue"));

        return op_ptr(op);
    }

    std::cerr<<"Unkown MCA operation - see manpage"<<std::endl;

    //better throw an exception here
    return op_ptr(nullptr);
}


