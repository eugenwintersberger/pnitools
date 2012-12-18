
#include "cmd_open.hpp"
#include <pni/utils/Types.hpp>
#include <pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

void cmd_open::setup(const std::vector<String> &cargs)
{
    _file_name = cargs[0];

    if(cargs.size() < 2)
        _current_group = "";
    else
        _current_group = cargs[1];
}

void cmd_open::execute(std::unique_ptr<environment> &env)
{
    NXFile f = NXFile::open_file(_file_name,false);
    if(_current_group == "")
        env = std::unique_ptr<environment>(new environment(f));
    else
        env = std::unique_ptr<environment>(new environment(f,_current_group));

}
