#include "cmd_ls.hpp"

#include <pni/utils/Types.hpp>
#include <pni/nx/NX.hpp>
#include <boost/tokenizer.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

//-----------------------------------------------------------------------------
void cmd_ls::setup(const std::vector<String> &cargs)
{
    if(cargs.size() != 0)
        _target = cargs[0];
}

void cmd_ls::print_content(const NXGroup &g) const
{
    for(auto o: g)
    {
        if(o.object_type() == pni::nx::NXObjectType::NXFIELD)
            std::cout<<"field";
        else if(o.object_type() == pni::nx::NXObjectType::NXGROUP)
            std::cout<<"group";

        std::cout<<"\t"<<o.name()<<std::endl;
    }
}

//-----------------------------------------------------------------------------
void cmd_ls::execute(std::unique_ptr<environment> &env)
{
    const NXGroup &cg = env->current_group();

    if(_target.empty())
    {
        //just print the content of the current group
        print_content(cg);
    }
    else
    {
        boost::char_separator<char> separator("/");
        boost::tokenizer<boost::char_separator<char> > t(_target,separator);
        NXGroup g(cg);
        for(auto iter = t.begin();iter!=t.end();++iter)
        {
            if(*iter == "..")
                g = g.parent();
            else
            {
                g = g[*iter];
            }
        }
        print_content(g);
    }

};
