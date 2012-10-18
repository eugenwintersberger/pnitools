#include "string_utils.hpp"

//-----------------------------------------------------------------------------
String trim(const String &s)
{
    size_t start_index = 0;
    for(auto iter = s.begin();iter!=s.end();++iter)
    {
        if((*iter == ' ')||(*iter=='\n')||(*iter=='\t')) 
        {
            start_index++;
            continue;
        }
        else break;
    }

    size_t stop_index = 0;
    for(auto iter = s.rbegin();iter!=s.rend();++iter)
    {
        if((*iter == ' ')||(*iter=='\n')||(*iter=='\t'))
        {
            stop_index++;
            continue;
        }
        else break;
    }

    return String(s,start_index,(s.size()-stop_index-start_index));
}

