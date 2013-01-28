
#include "cmd_open.hpp"
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

void cmd_open::setup(const std::vector<string> &cargs)
{
    _file_name = cargs[0];

    if(cargs.size() < 2)
        _current_group = "";
    else
        _current_group = cargs[1];
}

void cmd_open::execute(std::unique_ptr<environment> &env)
{
    nxfile f = nxfile::open_file(_file_name,false);
    if(_current_group == "")
        env = std::unique_ptr<environment>(new environment(f));
    else
        env = std::unique_ptr<environment>(new environment(f,_current_group));

}
