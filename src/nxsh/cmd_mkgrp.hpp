#pragma once

#include "command.hpp"

class cmd_mkgrp : public command
{
    private:
        String _class;
        String _name;
    public:
        virtual void setup(const std::vector<String> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
};


