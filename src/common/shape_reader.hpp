#pragma once

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>

#include <boost/regex.hpp>
using namespace pni::utils;

class shape_reader
{
    private:
        char _start_token;
        char _end_token;
        boost::regex e;
    public:
        shape_reader();
        shape_reader(char st,char et, String s);

        shape_t read(const String &s);
};

