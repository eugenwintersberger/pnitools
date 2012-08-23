//implementation of tool errors

#include "Exceptions.hpp"

//-----------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const CLIArgumentError &e)
    {
        return e.print(o);
    }

//-----------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const CLIOptionError &e)
    {
        return e.print(o);
    }

//-----------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const CLIError &e)
    {
        return e.print(o);
    }

//-----------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const FileTypeError &e)
    {
        return e.print(o);
    }

//-----------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const CLIHelpRequest &e)
    {
        return e.print(o);
    }
