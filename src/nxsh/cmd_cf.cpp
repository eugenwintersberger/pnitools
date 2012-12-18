#include <pni/utils/Types.hpp>
#include <pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

#include "cmd_cf.hpp"

void cmd_cf::setup(const std::vector<String> &cargs)
{
    _fname = cargs[0];
}

void cmd_cf::execute(std::unique_ptr<environment> &env)
{
    NXFile file = NXFile::create_file(_fname,"true",0);
    env = std::unique_ptr<environment>(new environment(file));
}
