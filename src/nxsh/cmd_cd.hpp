#pragma once

#include "command.hpp"

class cmd_cd : public command
{
    private:
        String _target;
    public:
        virtual void setup(const std::vector<String> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
};
