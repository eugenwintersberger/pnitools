#include "nx_object_path.hpp"

//-----------------------------------------------------------------------------
nx_object_path::nx_object_path(): _fname(""), _opath(""), _attrname("") {}

//-----------------------------------------------------------------------------
nx_object_path::nx_object_path(const String &path):
    _fname(""),
    _opath(""),
    _attrname("")
{
    //extract the filename (if present)
    size_t file_sep_pos = path.find_first_of(':');
    size_t attr_sep_pos = path.find_first_of('@');

    if(file_sep_pos != path.npos)
    {
        //if the path has a file portion we need to extract not the filename
        _fname = String(path,0,file_sep_pos);
    }

    if(attr_sep_pos != path.npos)
    {
        //extract the attribute name
        _attrname = String(path,attr_sep_pos+1,path.size()-attr_sep_pos);
    }

    //finally wee need to extract the object path
    size_t pstart = ((file_sep_pos == path.npos) ? 0 : file_sep_pos+1);
    size_t pstop = ((attr_sep_pos == path.npos) ? path.size() : attr_sep_pos);
    _opath = String(path,pstart,pstop - pstart);

    //now we have to fix the situation where the string passed is not a 
    //group path but a filename
    if(_opath.find_first_of('.')!=_opath.npos)
    {
        _fname = _opath;
        _opath = "";
    }

}

//-----------------------------------------------------------------------------
nx_object_path::nx_object_path(const String &f,const String &p,const String &a):
    _fname(f),
    _opath(p),
    _attrname(a)
{}

//-----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const nx_object_path &path)
{
    o<<path.filename()<<":"<<path.object_path();
    if(path.attribute_name() != "")
        o<<"@"<<path.attribute_name();

    return o;
}

//------------------------------------------------------------------------------
std::istream &operator>>(std::istream &i,nx_object_path &path)
{
    String pstring;
    i>>pstring;
    path = NXObjectPath(pstring);
    return i;
}
