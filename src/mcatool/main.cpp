/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: 03.06.2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include<iostream>
#include<memory>
#include<boost/program_options/options_description.hpp>
#include<boost/program_options/variables_map.hpp>
#include<boost/program_options/parsers.hpp>
#include<boost/program_options/positional_options.hpp>


#include<pni/utils/Types.hpp>
#include<pni/utils/ArrayFactory.hpp>
#include<pni/utils/Array.hpp>
#include<pni/utils/io/FIOReader.hpp>

#include "Operator.hpp"
#include "MaxOperator.hpp"
#include "SumOperator.hpp"
#include "RebinOperator.hpp"
#include "ScaleOperator.hpp"

using namespace pni::utils;
using namespace pni::io;
namespace po = boost::program_options;

class ProgramConfig{
    public:
        bool verbose;
        bool quiet;
};

void read_from_stdin(Float64Array &channels,Float64Array &data)
{
    std::vector<Float64> chvec;
    std::vector<Float64> dvec;
    Float64 ch,d;

    while(std::cin>>ch>>d)
    {
        chvec.push_back(ch);
        dvec.push_back(d);
    }

    channels = ArrayFactory<Float64>::create(Shape({chvec.size()}),chvec);
    data = ArrayFactory<Float64>::create(Shape({dvec.size()}),dvec);
}



//-----------------------------------------------------------------------------
Float64Array create_channel_data(size_t n)
{
    auto channels = ArrayFactory<Float64>::create(Shape({n}));

    for(size_t i=0;i<n;i++) channels[i] = Float64(i);
    return channels;
}

//-----------------------------------------------------------------------------
std::unique_ptr<Operator> select_operator(const po::variables_map &options) 
{
    String command = options["command"].as<String>();

    if(command == "max") 
        return std::unique_ptr<Operator>(new MaxOperator(options));

    if(command == "sum")
        return std::unique_ptr<Operator>(new SumOperator(options));

    if(command == "rebin")
        return std::unique_ptr<Operator>(new RebinOperator(options));

    if(command == "scale")
        return std::unique_ptr<Operator>(new ScaleOperator(options));

    std::cerr<<"Unkown MCA operation - see manpage"<<std::endl;

    //better throw an exception here
    return std::unique_ptr<Operator>(nullptr);
}

//=============================================================================
static const char usage_string[] = 
                      "Program usage:\n\n mcatool <command> <global options>"
                      " <command specific options> [input file]";


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

    ProgramConfig config;
    //----------------setting up the program options---------------------------
    //these options do not show up in the help text
    po::options_description hidden("Hidden options");
    hidden.add_options()
        ("command",po::value<String>(),"command string")
        ("input",po::value<String>(),"input file")
        ;

    po::options_description global("Global options");
    global.add_options()
        ("help,h","show help text")
        ("verbose,v",po::value<bool>()->zero_tokens(),"show verbose output")
        ("quiet,q",po::value<bool>()->zero_tokens(),"show no output")
        ("output,o",po::value<String>(),"output file")
        ("towcolumn,t",po::value<bool>()->zero_tokens(),
         "produce two column output")
        ("xcolumn",po::value<String>(),
         "name of the column with bin center values")
        ("ycolumn",po::value<String>(),
         "name of the column with actual MCA data")
        ;
    
    po::options_description rebin_options("Rebinning options");
    rebin_options.add_options()
        ("binsize,b",po::value<size_t>()->default_value(1),
         "Number of bins to collate")
        ("noxrebin",po::value<bool>()->zero_tokens()->default_value(false),
         "do not rebin the x-axis, use simple index instead")
        ;

    po::options_description scale_options("Scaling options");
    scale_options.add_options()
        ("center,c",po::value<size_t>()->default_value(0),
         "Index of center bin")
        ("delta,d",po::value<Float64>()->default_value(1),
         "Size of a bin")
        ("cvalue,x",po::value<Float64>()->default_value(0.),
         "position of the center bin")
        ;
    
    po::positional_options_description posopts;
    posopts.add("command",1);
    posopts.add("input",2);

    po::options_description visible("Allowed command line options");
    visible.add(global).add(rebin_options).add(scale_options);

    po::options_description all("All options");
    all.add(hidden).add(global).add(rebin_options).add(scale_options);

    //-------------------parse and store program options-----------------------
    po::variables_map options;
    po::store(po::command_line_parser(argc,argv).options(all)
              .positional(posopts).run(),options);
    po::notify(options);

    if(options.count("help"))
    {
        std::cout<<usage_string<<std::endl<<std::endl;
        std::cout<<visible<<std::endl<<std::endl;
        std::cout<<"See man mcatool for more information!"<<std::endl;
        return 1;
    }

    //-------------------------------------------------------------------------
    //here we will read data either from the standard in or from a file 
    Float64Array data,channels;

    if(options.count("input"))
    {
        FIOReader reader(options["input"].as<String>()); 
        data = reader.column<Float64Array>(options["ycolumn"].as<String>());
        //if no column for channel data is provided we will simply use the 
        //bin number as a center value for each bin
        if(options.count("xcolumn"))
            channels = reader.column<Float64Array>(options["xcolumn"].as<String>());
        else
            channels = create_channel_data(data.size());
    }
    else
    {
        read_from_stdin(channels,data);
    }


    //need to choose an operation
    if(!options.count("command"))
    {
        std::cerr<<"No command specified!"<<std::endl<<std::endl;
        std::cerr<<usage_string<<std::endl;
        return 1;
    }

    //select the proper operator
    std::unique_ptr<Operator> optr = select_operator(options);

    //run the operation
    (*optr)(channels,data);

    //output result data
    std::cout<<*optr<<std::endl;

    
    return 0;
}

