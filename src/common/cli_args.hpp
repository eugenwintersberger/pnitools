#pragma once

#include <vector>
#include <pni/utils/Types.hpp>

using namespace pni::utils;

/*!
\brief class managing CLI options

This class is used to hold CLI options in a form convineant for the
program_options class.
*/
class cli_args
{
    private:
        std::vector<String> _str_values;
        char **_str_ptrs;
         
    public:
        template<typename CTYPE> cli_args(const CTYPE &str_cont);
        ~cli_args();
        const char **argv() const;
        int argc() const;
};

//-----------------------------------------------------------------------------
template<typename CTYPE> cli_args::cli_args(const CTYPE &str_cont):
    _str_values(str_cont.size()),
    _str_ptrs(new char*[str_cont.size()])
{
    //copy original data
    std::copy(str_cont.begin(),str_cont.end(),_str_values.begin());

    //set the pointers 
    size_t index = 0;
    for(auto v: _str_values)
        _str_ptrs[index++] = v.c_str();

}
