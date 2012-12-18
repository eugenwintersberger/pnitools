#include "shape_reader.hpp"

shape_reader::shape_reader()
{
    e = boost::regex("(\\d+)");
}

shape_reader::shape_reader(char st,char et,String s)
{
    e = boost::regex("(\\d+)");
}

shape_t shape_reader::read(const String &s) 
{
    boost::match_results<String::const_iterator> what;
    boost::regex_search(s.begin(),s.end(),what,e);

    std::cout<<what.size()<<std::endl;
    for(auto match: what)
        std::cout<<match<<std::endl;

    return shape_t();

}
