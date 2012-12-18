#include "cmd_ls.hpp"

#include <pni/utils/Types.hpp>
#include <pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

//-----------------------------------------------------------------------------
void cmd_ls::setup(const std::vector<String> &cargs)
{
    //here we have nothing to do for now
}

//-----------------------------------------------------------------------------
void cmd_ls::execute(std::unique_ptr<environment> &env)
{
    const NXGroup &cg = env->current_group();

    for(auto o: cg)
    {
        if(o.object_type() == pni::nx::NXObjectType::NXFIELD)
            std::cout<<"field";
        else if(o.object_type() == pni::nx::NXObjectType::NXGROUP)
            std::cout<<"group";

        std::cout<<"\t"<<o.name()<<std::endl;
    }

};
