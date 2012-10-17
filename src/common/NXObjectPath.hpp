#ifndef __NXOBJECTPATH_HPP__
#define __NXOBJECTPHAT_HPP__

#include<pni/utils/Types.hpp>

using namespace pni::utils;

/*!
\brief representing path to an Nexus object

This class represents the path of an object within a Nexus file. 
A user can specify a Nexus object from the command line using the following
syntax
\code
<Filename>:<path to object>[@attribute name]
\endcode
Using this one can not only address a group or a field but also a particular
attribute.
The class provides access to the different components of such a path:
\li the file name
\li the path to the object with the file
\li and the optional attribute name

If the attribute name is an empty string the path refers to a group or field
object. If the path should only represent an internal path one can omit the file
name part.
*/
class NXObjectPath
{
    private:
        //! name of the file where the object is stored
        String _fname;
        //! path to the object
        String _opath;
        //! name of the attribute
        String _attrname;
    public:
        //====================constructor and destructor=======================
        //! default constructor
        explicit NXObjectPath();
        //! constructor
        explicit NXObjectPath(const String &p);

        //! constructor
        explicit NXObjectPath(const String &f,const String &p,const String &a);

        //! destructor
        ~NXObjectPath() {}

        //---------------------------------------------------------------------
        //! get file name
        String filename() const { return _fname; }
        //! get object path
        String object_path() const { return _opath; }
        //! get attribute name
        String attribute_name() const { return _attrname; }
};

//! output operator for NXObjectPath
std::ostream &operator<<(std::ostream &o,const NXObjectPath &path);

//! input operator for NXObjectPath
std::istream &operator>>(std::istream &i,NXObjectPath &path);

#endif
