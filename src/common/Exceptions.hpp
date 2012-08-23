/*
 * Exceptions.hpp
 *
 *  Created on: Sep 26, 2011
 *      Author: eugen
 */

#include<pni/utils/Types.hpp>
#include<pni/utils/Exceptions.hpp>

using namespace pni::utils;

#ifndef __CLI_EXCEPTIONS_HPP__
#define __CLI_EXCEPTIONS_HPP__

    /*!
    \brief command line argument error

    Thrown in cases where a command line argument (do not confuse this with an
    option has an inapropriate value or is missing).
    */
    class CLIArgumentError:public Exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            CLIArgumentError():Exception("CLIArgumentError"){}

            //-----------------------------------------------------------------
            /*! 
            \brief constructor

            \param r exception record
            \param d description
            */
            CLIArgumentError(const ExceptionRecord &r,const String &d):
                Exception("CLIArgumentError",r,d)
            {}
            
            //-----------------------------------------------------------------
            //! destructor
            ~CLIArgumentError() throw() {}

            //! output operator
            friend std::ostream &operator<<(std::ostream &o,const CLIArgumentError &e);
    };

    //-------------------------------------------------------------------------
    /*! 
    \brief command line option error

    Exception thrown in cases where a command line option is missing or has an
    inapropriate value.
    */
    class CLIOptionError:public Exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            CLIOptionError():Exception("CLIOptionError"){}

            //-----------------------------------------------------------------
            /*!
            \brief constructor

            \param r exception record
            \param d description
            */
            CLIOptionError(const ExceptionRecord &r,const String &d):
                Exception("CLIOptionError",r,d)
            {}

            //-----------------------------------------------------------------
            ~CLIOptionError() throw() {}

            //! output operator
            friend std::ostream &operator<<(std::ostream &o,const CLIOptionError &e);
    };

    //-------------------------------------------------------------------------
    /*!
    \brief general CLI error

    Thrown in case of a general CLI error not related to arguments or options.
    */
    class CLIError:public Exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            CLIError():Exception("CLIError"){}
            
            //-----------------------------------------------------------------
            /*!
            \brief constructor

            \param r exception record
            \param d description
            */
            CLIError(const ExceptionRecord &r,const String &d):
                Exception("CLIError",r,d)
            {}

            //-----------------------------------------------------------------
            //! destructor
            ~CLIError() throw() {}

            //! output operator
            friend std::ostream &operator<<(std::ostream &o,const CLIError &e);
    };

    //------------------------------------------------------------------------
    /*!
    \brief file type error

    This exception is thrown if the input or output file format cannot be
    handled.
    */
    class FileTypeError:public Exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            FileTypeError():Exception("FileTypeError"){}
            
            //-----------------------------------------------------------------
            /*!
            \brief constructor

            \param r exception record
            \param d description
            */
            FileTypeError(const ExceptionRecord &r,const String &d):
                Exception("FileTypeError",r,d)
            {}

            //-----------------------------------------------------------------
            //! destructor
            ~FileTypeError() throw() {}

            //! output operator
            friend std::ostream &operator<<(std::ostream &o,const FileTypeError &e);
    };


    //------------------------------------------------------------------------
    /*!
    \brief help request

    This is exception is not intended to manage an error at all. It is thrown in
    the case that a user makes a help request from the CLI.
    */
    class CLIHelpRequest:public Exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            CLIHelpRequest():Exception("CLIHelpRequest"){}
            
            //-----------------------------------------------------------------
            /*!
            \brief constructor

            \param r exception record
            \param d description
            */
            CLIHelpRequest(const ExceptionRecord &r,const String &d):
                Exception("CLIHelpRequest",r,d)
            {}

            //-----------------------------------------------------------------
            //! destructor
            ~CLIHelpRequest() throw() {}

            //! output operator
            friend std::ostream &operator<<(std::ostream &o,const CLIHelpRequest &e);
    };

#endif /* EXCEPTIONS_HPP_ */
