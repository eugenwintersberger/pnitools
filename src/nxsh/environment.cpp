#include <boost/tokenizer.hpp>
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

//-----------------------------------------------------------------------------
void environment::current_group(const String &path)
{
    //go one level up
    if(path == "..")
    {
        _current_group = _current_group.parent();
        return;
    }

    //need to check if the target is a group
    NXObject o = _current_group[path];
    if(o.object_type() == pni::nx::NXObjectType::NXFIELD)
    {
        std::cout<<"You cannot cd to a field!"<<std::endl;
    }
    else
    {
        _current_group = NXGroup(o);
    }
}

