#pragma once

#include "command.hpp"

class cmd_ls : public command
{
    public:
        virtual void setup(const std::vector<String> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
};
