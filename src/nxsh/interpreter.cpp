#include <boost/tokenizer.hpp>

#include "environment.hpp"
#include "interpreter.hpp"
#include "cmd_create.hpp"

//-----------------------------------------------------------------------------
 interpreter::interpreter():
    _current_env(new environment()),
    _cmd_stack()
{
    _cmd_stack["create"] = std::unique_ptr<command>(new cmd_create());
}

//-----------------------------------------------------------------------------
void interpreter::strip_command(const String &s,String
        &cname,std::vector<String> &cargs)
{   
    boost::char_separator<char> separator(" \t\n");
    boost::tokenizer<boost::char_separator<char> > t(s,separator);

    cname = *(t.begin());

    //copy arguments to a vector
    cargs = std::vector<String>();
    for(auto iter = ++t.begin();iter!=t.end();++iter)
        cargs.push_back(*iter);
}

//-----------------------------------------------------------------------------
void interpreter::run()
{
    char input_buffer[1024];
    //interpreter main loop
    while(true)
    {
        //print prompt
        prompt();

        //read user input
        std::cin.getline(input_buffer,1024,'\n');
        String input_str(input_buffer);

        //split command name and arguments
        String cname;
        std::vector<String> cargs;
        strip_command(input_str,cname,cargs);

        if(cname == "exit") break;

        //try to grap the command
        if(_cmd_stack.count(cname))
        {
            //execute the command
            try
            {
                _cmd_stack[cname]->setup(cargs);
                _cmd_stack[cname]->execute(_current_env);
            }
            catch(...)
            {
            }
        }
        else
            std::cerr<<"command not found"<<std::endl;

    }
    std::cout<<"Exit interpreter"<<std::endl;
}

//-----------------------------------------------------------------------------
void interpreter::prompt() 
{
    std::cout<<_current_env->get_current_path()<<">>";
}
