/*
 * Exceptions.hpp
 *
 *  Created on: Sep 26, 2011
 *      Author: eugen
 */
#pragma once
#include<pni/utils/Types.hpp>
#include<pni/utils/Exceptions.hpp>

using namespace pni::utils;

/*!
\brief file type error

This exception is thrown if the input or output file format cannot be
handled.
*/
class file_type_error:public Exception
{
    public:
        //-----------------------------------------------------------------
        //! default constructor
        file_type_error():Exception("FileTypeError"){}
        
        //-----------------------------------------------------------------
        /*!
        \brief constructor

        \param r exception record
        \param d description
        */
        file_type_error(const ExceptionRecord &r,const String &d):
            Exception("FileTypeError",r,d)
        {}

        //-----------------------------------------------------------------
        //! destructor
        ~file_type_error() throw() {}

        //! output operator
        friend std::ostream &operator<<(std::ostream &o,const file_type_error &e);
};
