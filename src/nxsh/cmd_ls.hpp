#pragma once

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>
#include <pni/nx/NX.hpp>

#include "command.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;

class cmd_ls : public command
{
    private:
        String _target;
        bool _show_attributes;

        void print_content(const NXGroup &g) const;
        void print_field(const NXField &o) const;
        void print_group(const NXGroup &o) const;
        void print_attribute(const NXAttribute &g) const;
    public:
        virtual void setup(const std::vector<String> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
};
