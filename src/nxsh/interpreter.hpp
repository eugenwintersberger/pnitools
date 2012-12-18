#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <pni/utils/Types.hpp>
#include <pni/nx/NX.hpp>

#include "environment.hpp"
#include "command.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;

class interpreter
{
    private:
        std::unique_ptr<environment> _current_env;
        std::map<String,std::unique_ptr<command> > _cmd_stack;

        void strip_command(const String &s,String &cname,std::vector<String> &cargs);
    public:
        interpreter(); 
        void run();
        void prompt() ;

};
