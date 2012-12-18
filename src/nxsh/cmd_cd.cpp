#include "cmd_cd.hpp"
#include <boost/tokenizer.hpp>

#include <pni/utils/Types.hpp>
#include <pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

//-----------------------------------------------------------------------------
void cmd_cd::setup(const std::vector<String> &cargs)
{
   _target = cargs[0]; 
}

//-----------------------------------------------------------------------------
void cmd_cd::execute(std::unique_ptr<environment> &env)
{
    boost::char_separator<char> separator("/");
    boost::tokenizer<boost::char_separator<char> > t(_target,separator);

    for(auto iter = t.begin();iter!=t.end();++iter)
        env->current_group(*iter);
}
