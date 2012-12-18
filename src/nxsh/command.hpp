#pragma once

#include "environment.hpp"

class command
{
    public:
        virtual void setup(const std::vector<String> &cargs) = 0;
        virtual void execute(std::unique_ptr<environment> &env) = 0;       

};

    


