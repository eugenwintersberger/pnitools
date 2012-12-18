#pragma once

#include <iostream>
#include <pni/utils/Types.hpp>
#include <pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;


class environment
{
    private:
        NXFile _file;
        NXGroup _current_group;
    public:
        //=====================constructor and destructor=======================
        //! default constructor
        environment() {}
        //----------------------------------------------------------------------
        /*! 
        \brief constructor

        Constructor taking only the file as an argument. The current group is in
        this case the root group /.
        \param file Nexus file to work on
        */
        environment(NXFile file);

        //---------------------------------------------------------------------
        /*! 
        \brief constructor

        Constructor with file and path to the new working group. 
        \param file file to work on 
        \param path the path to the new working group
        */
        environment(NXFile file,const String &path);

        //---------------------------------------------------------------------
        //! destructor
        ~environment();

        //======================public member functions========================
        //! get file reference
        const NXFile &file() const { return _file; }

        //---------------------------------------------------------------------
        //! get group reference
        const NXGroup &current_group() const { return _current_group; }

        void current_group(const String &path);

        //---------------------------------------------------------------------
        String get_current_path() const;

};
