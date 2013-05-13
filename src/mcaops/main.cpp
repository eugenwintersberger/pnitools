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
 * Created on: 03.06.2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include "mcaops.hpp"

//-----------------------------------------------------------------------------
/*! 
\ingroup mcaops_devel
\brief select the proper operator

\param options program options
\return unique pointer to the operator
*/
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

//=============================================================================
static const char usage_string[] = 
                      "Program usage:\n\n mcaops <command> <global options>"
                      " <command specific options> [input file]";

static const char command_string[] = 
            "Commands supported by mcaops:\n"
            "  sum\tum over all channels in a spectrum\n"
            "  max\tosition of maximum and its value\n"
            "  rebin\tre-bin the spectrum\n"
            "  scale\tscale the channel numbers to units\n"
            ;

//=============================================================================
int main(int argc,char **argv)
{
    //check the total number of arguments and options and show a message if
    //they are not correct.
    if(argc<2)
    {
        std::cout<<usage_string<<std::endl;
        std::cout<<"\nuse mcatool -h for more information"<<std::endl;
        return 1;
    }
    configuration config;

    //----------------setting up the program options---------------------------
    //these options do not show up in the help text
    config.add_argument(config_argument<string>("command",1));
    config.add_argument(config_argument<string>("input",2));

    //-------------------------------------------------------------------------
    //global options valid for all commands
    config.add_option(config_option<bool>("help","h","show help text",false));
    config.add_option(config_option<bool>("verbose","v","show verbose output",false));
    config.add_option(config_option<bool>(
                "header","","write headers before output",false));
    config.add_option(config_option<string>("xcolumn","",
                "name of the column with bin center values"));
    config.add_option(config_option<string>("ycolumn","",
                "name of the column with actual MCA data"));
   
    //-------------------------------------------------------------------------
    //options for the rebin command
    configuration rebin_config;
    rebin_config.add_option(config_option<size_t>("binsize","b",
                "number of bins to collate",1));
    rebin_config.add_option(config_option<bool>("noxrebin","",
                "do not rebin the x-axis, use simple indices instead",false));

    //-------------------------------------------------------------------------
    //options for the scale command
    configuration scale_config;
    scale_config.add_option(config_option<size_t>("center","c",
                "index of center bin"));
    scale_config.add_option(config_option<float64>("delta","d",
                "size of a bin"));
    scale_config.add_option(config_option<float64>("cvalue","x",
                "position of the center bin"));
   

    //-------------------parse and store program options-----------------------
    std::vector<string> args = cliargs2vector(argc,argv);
    parse(config,args);

    if(config.has_option("help"))
    {
        std::cerr<<usage_string<<std::endl<<std::endl;
        std::cerr<<command_string<<std::endl;
        std::cerr<<config<<std::endl;
        std::cerr<<std::endl<<"Options for the scale command:"<<std::endl;
        std::cerr<<scale_config<<std::endl;
        std::cerr<<std::endl<<"Options for the rebin command:"<<std::endl;
        std::cerr<<rebin_config<<std::endl;
        std::cerr<<"See 'man mcaops' for more information!"<<std::endl;
        return -1;
    }

    return 0;        

    //-------------------------------------------------------------------------
    //here we will read data either from the standard in or from a file 
    operation::array_type data,channels;

    if(config.has_option("input"))
    {
        //----------------open the file holding the data-----------------------
        string filename = config.value<string>("input");

        fio_reader reader;
        //read data from a file
        try{
            reader = fio_reader(filename); 
        }
        catch(...)
        {
            std::cerr<<"Error reading file "<<filename<<"!"<<std::endl;
            return 1;
        }

        //----------------read MCA data form the appropriate column-------------
        string ycolumn;
        if(config.has_option("ycolumn"))
        {
            ycolumn = config.value<string>("ycolumn");
        }
        else
        {
            //if the file holds more than one column we have to abort the
            //program as we cannot know from which column to read data
            if(reader.ncolumns() != 1)
            {
                std::cerr<<"File "<<filename<<" contains more than one ";
                std::cerr<<"columns - specify from which to read MCA data!";
                std::cerr<<std::endl;
                return 1;
            }
            
            //if the file contains only one column we can assume that this
            //column holds the MCA data
#ifdef NOFOREACH
            for(auto iter=reader.begin();iter!=reader.end();iter++)
            {
                auto c = *iter;
#else
            for(auto c: reader) 
            {
#endif
                ycolumn = c.name();
            }

        }

        //finally read column data from the file
        try
        {
            
            data = operation::array_type(operation::shape_type{reader.nrecords()},
                            reader.column<operation::array_type::storage_type>(ycolumn));
        }
        catch(key_error &error)
        {
            std::cerr<<"Error reading MCA data from column "<<ycolumn;
            std::cerr<<" - column does not exist!"<<std::endl;
            std::cerr<<"The following columns are available in this file:";
            std::cerr<<std::endl;
#ifdef NOFOREACH
            for(auto iter=reader.begin();iter!=reader.end();iter++)
            {
                auto c = *iter;
#else
            for(auto c: reader)
            {
#endif
                std::cerr<<c<<std::endl;
            }
            return 1;
        }
        catch(...)
        {   
            std::cerr<<"Error reading MCA data from column ";
            std::cerr<<config.value<string>("ycolumn")<<"!";
            return 1;
        }

        //if no column for channel data is provided we will simply use the 
        //bin number as a center value for each bin
        if(config.has_option("xcolumn"))
            try{
                channels = operation::array_type(operation::shape_type{reader.ncolumns()},
                           reader.column<operation::array_type::storage_type>(config.value<string>("xcolumn")));
            }
            catch(key_error &error)
            {
                std::cerr<<"Error reading bin data from column ";
                std::cerr<<config.value<string>("xcolumn");
                std::cerr<<" - column does not exist!"<<std::endl;
                return 1;
            }
            catch(...)
            {
                std::cerr<<"Error reading bin data from column ";
                std::cerr<<config.value<string>("xcolumn")<<"!"<<std::endl;
                return 1;
            }
        else
            channels = create_channel_data(data.size());
    }
    else
    {
        read_from_stdin(channels,data);
    }


    //need to choose an operation
    if(!config.has_option("command"))
    {
        std::cerr<<"No command specified!"<<std::endl<<std::endl;
        std::cerr<<usage_string<<std::endl;
        return 1;
    }

    //select the proper operator
    op_ptr optr = select_operator(config,scale_config,rebin_config);

    //run the operation
    (*optr)(channels,data);

    if(config.has_option("header"))
        std::cout<<"#chan data"<<std::endl;

    //output result data
    std::cout<<*optr<<std::endl;

    
    return 0;
}

