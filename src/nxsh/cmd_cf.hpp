#pragma once

#include "command.hpp"

//! create a file command
class cmd_cf : public command
{
    private:
        String _fname;
    public:
        virtual void setup(const std::vector<String> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
};


