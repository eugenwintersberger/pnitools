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
        for(size_t row_index=0;row_index<data_tab.nrows();++row_index)
        {
            for(auto key: keys)
            {
                column_t::iterator iter = data_tab[key].begin();
                std::advance(iter,row_index);
                std::cout<<*iter<<"\t";
            }

            std::cout<<std::endl;
        }
     
        /*
        //read all the data
        std::list<array> columns;
        for(auto p: sources) columns.push_back(read_source(p));
        
        //we are working only with const_iterators as we do not intend to change
        //any value.
        array_citer_t stop_iter = ((const array &)columns.front()).end();
        record_t record;
        for(const array& c: columns) record.push_back(c.begin());


        //print output
        while(record.front()!=stop_iter)
        {
            //output data
            for(array_citer_t& iter: record) std::cout<<*(iter++)<<"\t";

            std::cout<<std::endl;
        }
        */

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


