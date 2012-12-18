#include <pni/utils/Types.hpp>
#include <pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

#include "cmd_create.hpp"

//-----------------------------------------------------------------------------
void cmd_create::setup(const std::vector<String> &cargs)
{
    String what = cargs[0];
    std::vector<String> wargs;

    //create the arguments for the creator
    for(auto iter = ++cargs.begin();iter!=cargs.end();++iter)
        wargs.push_back(*iter);

    //create a new instance of the creator
    if(what == "group")
        _what = std::unique_ptr<object_creator>(new group_creator());
    else if(what == "file")
        _what = std::unique_ptr<object_creator>(new file_creator());
    else
    {
        std::cerr<<"I do not know how to create this!"<<std::endl;
        return;
    }

    //setup the creator
    _what->setup(wargs);
}

//-----------------------------------------------------------------------------
void cmd_create::execute(std::unique_ptr<environment> &env)
{
    _what->execute(env);
}

//-----------------------------------------------------------------------------
void file_creator::setup(const std::vector<String> &cargs)
{
    _file_name = cargs[0];
}

//-----------------------------------------------------------------------------
void file_creator::execute(std::unique_ptr<environment> &env)
{
    NXFile file = NXFile::create_file(_file_name,"true",0);
    env = std::unique_ptr<environment>(new environment(file));
}

//-----------------------------------------------------------------------------
void group_creator::setup(const std::vector<String> &cargs)
{
    _group_name = cargs[0];
    if(cargs.size()<2)
        _group_class = "";
    else
        _group_class = cargs[1];

}

//-----------------------------------------------------------------------------
void group_creator::execute(std::unique_ptr<environment> &env)
{
    const NXGroup &cg = env->current_group();
   
    if(_group_class == "")
        cg.create_group(_group_name);
    else
        cg.create_group(_group_name,_group_class);
}
