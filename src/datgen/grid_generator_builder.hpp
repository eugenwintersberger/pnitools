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
// Created on: 8 May, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/configuration.hpp>

//forward declaration
class grid_generator;

//!
//! \ingroup datgen_devel
//! \brief grid generator builder
//! 
//! This builder class creates an instance of grid_generator from the user 
//! input configuration. 
//! 
class grid_generator_builder
{
    private:
        //!
        //! \brief get first value from configuration
        //! 
        //! Extracts the first value of the grid from the configuration
        //! instance. 
        //! 
        //! \throws cli_option_error if the "begin" option is not available
        //! 
        //! \param config reference to the user configuration
        //! \return first value of x-grid
        //!
        static pni::core::float64 
            get_first_value(const pni::core::configuration &config);


        //--------------------------------------------------------------------
        //!
        //! \brief get last value from configuration
        //! 
        //! Extract the last value of the grid from the user configuration.
        //!
        //! \throws cli_option_error if the "end" option is not availble 
        //! 
        //! \param config reference to the user configuration
        //! \return last value of the x-grid
        //! 
        static pni::core::float64 
            get_last_value(const pni::core::configuration &config);

        //--------------------------------------------------------------------
        //!
        //! \brief get number of points from configuration
        //! 
        //! Extracts the number of grid points from the user configuration
        //! 
        //! \throws cli_option_error if the "steps" option is not available.
        //! 
        //! \param config reference to user configuration
        //! \return number of grid points
        //!
        static size_t get_npoints(const pni::core::configuration &config);

        //--------------------------------------------------------------------
        //!
        //! \brief get step width 
        //!
        //! Computes the step width for the grid. 
        //! 
        //! \throws range_error if not first<last
        //! 
        //! \param first the first value of the grid
        //! \param last  the last value of the grid
        //! \param npoints number of grid points
        //! \return step width along x
        //! 
        static pni::core::float64 get_delta(pni::core::float64 first,
                                            pni::core::float64 last,
                                            size_t npoints);
    public:
        //! 
        //! \brief create the grid generator
        //! 
        //! Create a build generator from the configuration passed by the user 
        //! via command line arguments. The function also performs some sanity 
        //! checks on the input data. 
        //! 
        //! \throws cli_option_error if one of the required command line options
        //!                          has not been provided by the user
        //! \throws range_error if the last value of the grid is smaller than
        //!                     the first one
        //! 
        //! \param config user configuration
        //! \return instance of grid_generator
        //! 
        static grid_generator build(const pni::core::configuration &config); 
};
