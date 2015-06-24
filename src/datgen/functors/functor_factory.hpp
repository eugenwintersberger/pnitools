//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// pnitools is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pnitools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
// Created on: Jun 9, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/configuration.hpp>
#include "functor.hpp"
#include "../options_splitter.hpp"

//! 
//! \ingroup datgen_devel
//! \brief functor factory class
//! 
//! This class is used to create concrete functors. It is stateless and all 
//! work is done via static member functions.
//! 
class functor_factory
{
    private:
        //!
        //! \brief create uniform functor
        //!
        //! Creates an instance of a uniform functor. 
        //! \param args command line options associated with this instance
        //! \return unique pointer to the functor instance
        //!
        static functor::pointer_type create_uniform(const args_vector &args);

        //--------------------------------------------------------------------
        //! 
        //! \brief create uniform configuration
        //! 
        //! Create the configuration for a uniform functor
        //! \return configuration instance
        //! 
        static pni::core::configuration create_uniform_config();

        //--------------------------------------------------------------------
        //!
        //! \brief create linear functor
        //!
        //! Creates an instance of a linear functor.
        //! \param args command line options associated with this instance
        //! \return unique pointer to the functor instance
        //!
        static functor::pointer_type create_linear(const args_vector &args);
        
        //--------------------------------------------------------------------
        //! 
        //! \brief create linear configuration
        //! 
        //! Create the configuration for a linear functor
        //! \return configuration instance
        //! 
        static pni::core::configuration create_linear_config();

        //--------------------------------------------------------------------
        //!
        //! \brief create gaussian functor
        //!
        //! Creates an instnace of a Gaussian functor.
        //! \param args command line options associated with this instance
        //! \return unique pointer ot the functo instance
        //!
        static functor::pointer_type create_gauss(const args_vector &args);
        
        //--------------------------------------------------------------------
        //! 
        //! \brief create gauss configuration
        //! 
        //! Create the configuration for a gauss functor
        //! \return configuration instance
        //! 
        static pni::core::configuration create_gauss_config();

        //---------------------------------------------------------------------
        //!
        //! \brief create error message 
        //! 
        //! Return the error message in situations where unkown options or 
        //! arguments where passed to a functor
        //! 
        //! \param res residual arguments not parsed
        //! \return error message as string
        //!
        static pni::core::string get_cli_error_message(const args_vector &res);
    public:
        //!
        //! \brief create functor 
        //! 
        //! Static function which creates a functor. All required configuration 
        //! is drawn from the name of the functor and the particular 
        //! command line options provided along with this name. 
        //!
        //! \param name the name of the functor to create
        //! \param args list of command line arguments for the functor
        //! \return unique pointer to the newly created functor instance
        //!
        static functor::pointer_type create(const pni::core::string &name,
                                            const args_vector &args);

        //--------------------------------------------------------------------
        //!
        //! \brief get configuration for a functor
        //! 
        //! Returns the configuration for a particular functor determined 
        //! by its name.
        //! 
        //! \param name the name of the functor
        //! \return the configuration for this very functor
        //! 
        static pni::core::configuration 
            config(const pni::core::string &name);
};
