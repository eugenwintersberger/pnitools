#ifndef __FILE_HPP__
#define __FILE_HPP__

#include <pni/utils/Types.hpp>
#include <boost/filesystem.hpp>

using namespace pni::utils;
namespace fs = boost::filesystem;

    /*!
    \ingroup common_code
    \brief class describing a single file

    This class represents a single file stored somewhere on the file system. Its
    only purpose is to give easy access to all the parameters of the file.
    */
    class File
    {
        private:
            //! boost path object representing the file
            fs::path _path;
        public:
            //========================constructors and destructor==============
            //! default constructor
            File():_path() {}

            //-----------------------------------------------------------------
            /*!
            \brief constructor

            Constructor taking a string representing the full path to the file.
            \param f path to the file
            */
            File(const String &path);

            //-----------------------------------------------------------------
            //! destructor
            ~File() {}

            //=================general purpose methods=========================
            //! return the name of the file
            String name() const;

            //! return the path to the file
            String path() const;

            //! return the extension of the file
            String extension() const;

            //! true if this is a regular file
            bool is_file() const;
    };


#endif
