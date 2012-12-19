#include "cmd_ls.hpp"

#include <boost/tokenizer.hpp>


//-----------------------------------------------------------------------------
void cmd_ls::setup(const std::vector<String> &cargs)
{
    if(cargs.size() != 0)
        _target = cargs[0];
}

//------------------------------------------------------------------------------
void cmd_ls::print_field(const NXField &f) const
{
    auto s = f.shape<shape_t>();

    std::cout<<"field\t";
    std::cout<<f.name()<<"\t";
    std::cout<<f.type_id()<<"\t";

    std::cout<<"( ";
    for(auto v: s)
        std::cout<<v<<" ";

    std::cout<<" )"<<std::endl;
}

//------------------------------------------------------------------------------
void cmd_ls::print_group(const NXGroup &g) const
{
    std::cout<<"group\t";
    std::cout<<g.name();

    if(g.has_attr("NX_class"))
    {
        String attr_str;
        g.attr("NX_class").read(attr_str);
        std::cout<<"\t class = "<<attr_str;
    }

    std::cout<<std::endl;

}

//------------------------------------------------------------------------------
void cmd_ls::print_attribute(const NXAttribute &g) const
{

}

//------------------------------------------------------------------------------
void cmd_ls::print_content(const NXGroup &g) const
{
    for(auto o: g)
    {
        if(o.object_type() == pni::nx::NXObjectType::NXFIELD)
            print_field(NXField(o));
        else if(o.object_type() == pni::nx::NXObjectType::NXGROUP)
            print_group(NXGroup(o));

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

    _target.clear();

};
