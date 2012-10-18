#ifndef __STRINGUTILS_HPP__
#define __STRINGUTILS_HPP__

#include<pni/utils/Types.hpp>

using namespace pni::utils;

/*!
\brief trim a string

Remove leading and trailing blanks from a string.
\param s string to trim
\return trimmed string
*/
String trim(const String &s);

#endif
