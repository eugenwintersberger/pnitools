
#include "Exceptions.hpp"
#include "File.hpp"

//-----------------------------------------------------------------------------
    File::File(const String &path):
        _path(path)
    {
        if(!fs::is_regular_file(_path))
        {
            throw FileError(EXCEPTION_RECORD,"File ["+path+"] is not a regular"
                            "file!");
        }
    }

//-----------------------------------------------------------------------------
    String File::name() const
    {
        return _path.filename().string();
    }

//-----------------------------------------------------------------------------
    String File::base() const
    {
        return _path.parent_path().string(); 
    }

//-----------------------------------------------------------------------------
    String File::extension() const
    {
        return _path.extension().string();
    }

//-----------------------------------------------------------------------------
    String File::path() const
    {
        return _path.string();
    }
