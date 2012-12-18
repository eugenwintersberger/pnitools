#pragma once

#include "command.hpp"

//-----------------------------------------------------------------------------
class object_creator
{
    public:
        virtual void setup(const std::vector<String> &cargs) = 0;
        virtual void execute(std::unique_ptr<environment> &env) = 0;
};

//-----------------------------------------------------------------------------
class group_creator : public object_creator
{
    private:
        String _group_name;
        String _group_class;
    public:
        virtual void setup(const std::vector<String> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
};

//-----------------------------------------------------------------------------
class file_creator : public object_creator
{
    private:
        String _file_name;
    public:
        virtual void setup(const std::vector<String> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
};

//-----------------------------------------------------------------------------
//! create something
class cmd_create : public command
{
    private:
        //! the creator object that decides what to do
        std::unique_ptr<object_creator> _what;
    public:
        virtual void setup(const std::vector<String> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
};


