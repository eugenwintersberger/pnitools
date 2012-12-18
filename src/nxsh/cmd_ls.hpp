#pragma once

#include "command.hpp"

class cmd_ls : public command
{
    private:
        String _target;

        void print_content(const NXGroup &g) const;
    public:
        virtual void setup(const std::vector<String> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
};
