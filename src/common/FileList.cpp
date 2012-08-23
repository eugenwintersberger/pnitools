#include "FileList.hpp"
#include <boost/format.hpp>



//-----------------------------------------------------------------------------
    bool FileList::_fill_from_num_range(const String &p)
    {

        nrseparator sep(":");
        nrtokenizer token(p,sep);
        size_t start = 0;
        size_t stop = 0;
        size_t stride = 1;
        String p_template;

        size_t index = 0;
        for(auto iter = token.begin(); iter!= token.end();++iter)
        {
            std::stringstream ss(*iter);
            switch(index)
            {
                case 0: ss>>p_template; break;
                case 1: ss>>start; break;
                case 2: ss>>stop; break;
                case 3: ss>>stride; break;
            }
            index++;
        }

        if(index<2) return false;

        index = start;
        do
        {
            std::stringstream ss;
            ss<<boost::format(p_template)%index;
            _file_list.push_back(ss.str());
            index += stride;

        }while(index<=stop);
        
        

        return true;

    }
        
