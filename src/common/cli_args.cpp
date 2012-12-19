#include "cli_args.hpp"

//-----------------------------------------------------------------------------
cli_args::~cli_args()
{
    _str_values.clear();
    if(_str_ptrs) delete [] _str_ptrs;
    _str_ptrs = nullptr;
}

//-----------------------------------------------------------------------------
const char **cli_args::argv() const
{
    return (const char **)_str_ptrs;
}

//-----------------------------------------------------------------------------
int cli_args::argc() const
{
    return _str_values.size();
}
