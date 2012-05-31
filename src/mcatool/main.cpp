#include<iostream>
#include<boost/program_options/options_description.hpp>
#include<boost/program_options/variables_map.hpp>
#include<boost/program_options/parsers.hpp>
#include<boost/program_options/positional_options.hpp>


#include<pni/utils/Types.hpp>
#include<pni/utils/ArrayFactory.hpp>
#include<pni/utils/Array.hpp>
#include<pni/utils/io/FIOReader.hpp>

using namespace pni::utils;
using namespace pni::io;
namespace po = boost::program_options;

class ProgramConfig{
    public:
        bool verbose;
        bool quiet;
};

class Operator
{
    public:
        Operator(const po::variables_map &config){}
        virtual ~Operator() {}

        virtual void operator()(const Float64Array bins,
                        const Float64Array data) = 0;
};

Float64Array create_channel_data(size_t n)
{
    auto channels = ArrayFactory<Float64>::create(Shape({n}));

    for(size_t i=0;i<n;i++) channels[i] = Float64(i);
    return channels;
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
    FIOReader reader(options["input"].as<String>());
    
    auto data = reader.column<Float64Array>(options["ycolumn"].as<String>());
    Float64Array channels;

    //if no column for channel data is provided we will simply use the 
    //bin number as a center value for each bin
    if(options.count("xcolumn"))
        channels = reader.column<Float64Array>(options["xcolumn"].as<String>());
    else
        channels = create_channel_data(data.size());

    for(size_t i=0;i<channels.size();i++)
        std::cout<<channels[i]<<"\t"<<data[i]<<std::endl;

    
    //need to choose an operation
     

    
    return 0;
}

