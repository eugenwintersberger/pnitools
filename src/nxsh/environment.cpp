#include "environment.hpp"

//-----------------------------------------------------------------------------
environment::environment(NXFile file):_file(file)
{
    _current_group = file["/"];
}

//-----------------------------------------------------------------------------
environment::environment(NXFile file,const String &path):_file(file)
{
    _current_group = file[path];
}

//-----------------------------------------------------------------------------
environment::~environment()
{
    _current_group.close();
    _file.close();
}

//-----------------------------------------------------------------------------
String environment::get_current_path() const
{
    return _file.name()+":"+_current_group.path();
}

