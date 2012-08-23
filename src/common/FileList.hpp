#ifndef __FILELIST_HPP__
#define __FILELIST_HPP__

#include <pni/utils/Types.hpp>
#include <list>
#include "File.hpp"

using namespace pni::utils;


    /*!
    \brief an iterable list of files

    This is an iterable list of valid regular files. During list creation all
    files are checked for their existance and validity. This should avoid that a
    program stops after a maybe long time of operation due to a simple file
    error.
    */
    class FileList
    {
        private:
            std::list<File> _file_list; 
        
        public:
            //==================public types====================================
            typedef File value_type;
            typedef std::list<File>::iterator iterator;
            typedef std::list<File>::const_iterator const_iterator;

            //==================constructors and destructor=====================
            //! default constructor
            FileList():_file_list() {}

            //------------------------------------------------------------------
            /*! 
            \brief constructor
            
            Construct obejct from a list of paths. The paths are passed in an
            arbitary container type.
            \tparam CTYPE container type
            \param pl path list
            */
            template<typename CTYPE> FileList(const CTYPE &pl):
                _file_list()
            {
                for(auto po: pl)
                {
                    //now we have to handle this thing - for now we assume that
                    //this a simple file
                    _file_list.push_back(po);
                }
            }

            //================query methods=====================================
            //! get number of files
            size_t size() const { return _file_list.size(); }

            //=============iterator related methods=============================
            //! get non-const iterator to first element
            iterator begin() { return _file_list.begin(); }

            //------------------------------------------------------------------
            //! get non-const iterator to last+1 delement
            iterator end() { return _file_list.end(); }

            //------------------------------------------------------------------
            //! get const iterator to first element
            const_iterator begin() const { return _file_list.begin(); }

            //------------------------------------------------------------------
            //! get const iterator to last+1 element
            const_iterator end() const { return _file_list.end(); }
            

    };

#endif
