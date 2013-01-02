#include "cmd_ls.hpp"
#include <pni/utils/config/cli_args.hpp>
#include <pni/utils/config/config_parser.hpp>
#include <pni/utils/config/configuration.hpp>

#include <boost/tokenizer.hpp>

//-----------------------------------------------------------------------------
cmd_ls::cmd_ls() { }

//-----------------------------------------------------------------------------
void cmd_ls::setup(const std::vector<String> &cargs)
{
    //create configuration setup
    configuration config;
    config.add_option(config_option<bool>("attributes","a",
                                          "show attributes",false,
                                          &_show_attributes));
    config.add_option(config_option<bool>("long","l",
                                          "show detailed information",false,
                                          &_show_long));
    config.add_argument(config_argument<String>("target",-1,"",&_target));

    cli_args args(cargs);
    parse(config,args.argc(),args.argv());
}

//------------------------------------------------------------------------------
void cmd_ls::print_field(const NXField &f) const
{
    auto s = f.shape<shape_t>();

    std::cout<<"field\t";
    std::cout<<f.name();

    if(_show_long)
    {
        std::cout<<"\t"<<f.type_id()<<"\t";

        std::cout<<"( ";
        for(auto v: s)
            std::cout<<v<<" ";

        std::cout<<" )";
    }

    std::cout<<std::endl;
}

//------------------------------------------------------------------------------
void cmd_ls::print_group(const NXGroup &g) const
{
    std::cout<<"group\t";
    std::cout<<g.name();
   
    if(_show_long)
    {
        if(g.has_attr("NX_class"))
        {
            String attr_str;
            g.attr("NX_class").read(attr_str);
            std::cout<<":"<<attr_str;
        }
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
