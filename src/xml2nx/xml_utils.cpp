#include "xml_utils.hpp"

//-----------------------------------------------------------------------------
shape_t dimensions2shape(const tree::ptree &dims)
{
    size_t rank = dims.get<size_t>("<xmlattr>.rank");
    shape_t s(rank);

    //initialize the shape with zero
    std::fill(s.begin(),s.end(),0);

    for(auto dim: dims)
    {
        if(dim.first != "dim") continue;

        auto index = dim.second.get<size_t>("<xmlattr>.index");
        auto value = dim.second.get<size_t>("<xmlattr>.value");
        s[index-1] = value;
    }

    return s;
}
