//implementation of tool errors

#include "exceptions.hpp"

std::ostream &operator<<(std::ostream &o,const file_type_error &e)
{
    return e.print(o);
}
