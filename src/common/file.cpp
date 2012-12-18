
#include "exceptions.hpp"
#include "file.hpp"

//-----------------------------------------------------------------------------
file::file(const String &path):
    _path(path)
{
    if(!fs::is_regular_file(_path))
    {
        throw FileError(EXCEPTION_RECORD,"File ["+path+"] is not a regular"
                        "file!");
    }
}

//-----------------------------------------------------------------------------
String file::name() const
{
    return _path.filename().string();
}

//-----------------------------------------------------------------------------
String file::base() const
{
    return _path.parent_path().string(); 
}

//-----------------------------------------------------------------------------
String file::extension() const
{
    return _path.extension().string();
}

//-----------------------------------------------------------------------------
String file::path() const
{
    return _path.string();
}
