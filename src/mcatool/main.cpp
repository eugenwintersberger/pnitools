#include<iostream>
#include<boost/program_options/options_description.hpp>
#include<boost/program_options/variables_map.hpp>
#include<boost/program_options/parsers.hpp>
#include<boost/program_options/positional_options.hpp>


#include<pni/utils/Types.hpp>

using namespace pni::utils;
namespace po = boost::program_options;

class ProgramConfig{
    public:
        bool verbose;
        bool quiet;
};

String read_command(char **argv)
{
    String command(argv[1]);
    return command;
}

static const char usage_string[] = 
                      "Program usage:\n\n mcatool <command> <global options>"
                      " <command specific options> [input file]";


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
    po::store(po::command_line_parser(argc,argv).options(all).positional(posopts).run(),options);
    po::notify(options);

    if(options.count("help"))
    {
        std::cout<<usage_string<<std::endl<<std::endl;
        std::cout<<visible<<std::endl<<std::endl;
        std::cout<<"See man mcatool for more information!"<<std::endl;
        return 1;
    }



    
    return 0;
}
