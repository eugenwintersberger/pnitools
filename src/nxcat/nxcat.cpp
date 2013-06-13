/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: Jan 16,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "nxcat.hpp"
#include "../common/config_utils.hpp"
#include "../common/nexus_utils.hpp"
#include "../common/array_utils.hpp"


static const string prg_name = "nxcat";
static const string help_hdr = "nxcat usage:";

int main(int argc,char **argv)
{
    //--------------------setup program configuration--------------------------
    configuration conf = create_configuration();

    if(parse_cli_opts(argc,argv,prg_name,conf))
        return 1;

    if(check_help_request(conf,help_hdr))
        return 1;


    try
    {
        //----------------------parse the input data----------------------------
        //get the source string
        sources_list sources;
        for(auto source_path: conf.value<string_list>("source"))
            sources.push_back(path_from_string(source_path));

        //table with data
        table_t data_tab = read_table(sources);

        auto keys = data_tab.keys<string_list>();
        if(conf.value<bool>("header"))
        {
            for(auto key: keys)
                std::cout<<"#"<<data_tab[key].name()<<" ("
                         <<data_tab[key].unit()<<")"<<std::endl;
        }

        //get start and stop indices
        size_t start_index = conf.value<size_t>("start");
        //if the stop index is 0 we print everything
        size_t end_index   = conf.value<size_t>("end")==0 ? data_tab.nrows() : 
                             conf.value<size_t>("end");

        //loop over all rows
        for(size_t row_index=start_index;row_index<end_index;++row_index)
        {
            //loop over all columns - this is currently not very nice 
            //but works and seems to be fast enough
            for(auto key: keys)
            {

                column_t::iterator iter = data_tab[key].begin();
                std::advance(iter,row_index);
                std::cout<<*iter<<"\t";
            }

            std::cout<<std::endl;
        }

    }
    catch(nxgroup_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(memory_not_allocated_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(...)
    {
        std::cerr<<"Something went wrong!"<<std::endl;
        return 1;
    }

    return 0;
}


