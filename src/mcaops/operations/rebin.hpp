//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// libpniutils is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniutils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
// Created on: 03.06.2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
///
#pragma once

#include <pni/core/types.hpp>
#include "operation.hpp"

//!
//! \ingroup mcaops_ops_devel
//! \brief implementation of rebining
//! 
//! This class provides the implementation of the rebining operation for 
//! MCA histograms. 
//!
class rebin:public operation
{
    private:
        //! number of bins to collate
        size_t _bsize; 
        //! flag for not rebining the x-axis
        bool   _noxrebin;
        //! flag for normalization
        bool   _norm;

        array_type _new_channels;
        array_type _new_mca;

        //!
        //! \brief create a new array a new array
        //! 
        //! Create a new array instance with the required size. 
        //!
        //! \param size number of elements 
        //! \return new array instance
        //!
        static array_type create_array(size_t size);

        //!
        //! \brief compute new size
        //!
        //! Compute the size of the rebinned data. This is not a static 
        //! method as is required access to the bin size of the new data set 
        //! which is stored in _bsize; 
        //!
        //! \param orig_channels number of channels in the input data
        //! \return number of channels in the output data
        //!
        size_t get_new_channels(size_t orig_channels) const;

        static size_t distance(data_range range);

        array_type create_norm(size_t orig_channels,size_t new_channels) const;

        //!
        //! 
        template<typename ITERT1,
                 typename ITERT2>
        void reduce_data(ITERT1 ifirst,ITERT1 ilast,ITERT2 ofirst,ITERT2 olast)
        {
            auto ilower = ifirst;
            auto iupper = ifirst;
            std::advance(iupper,_bsize);

            for(; ofirst != olast;++ofirst) 
            {
                *ofirst = std::accumulate(ilower,iupper,0);

                //now we need to advance
                std::advance(ilower,_bsize);
                if(std::distance(iupper,ilast)<_bsize) iupper = ilast;
                else
                    std::advance(iupper,_bsize);
            }
            
        }

    public:
        //---------------------------------------------------------------------
        //! default constructor
        rebin();

        //---------------------------------------------------------------------
        //! destructor
        ~rebin(){}

        //---------------------------------------------------------------------
        virtual args_vector configure(const args_vector &args);

        //---------------------------------------------------------------------
        //! get bin size
        size_t bin_size() const { return _bsize; } 

        //---------------------------------------------------------------------
        //! set bin size
        void bin_size(size_t v) { _bsize = v; }

        //---------------------------------------------------------------------
        //! perform no x-rebinning
        void no_x_rebinning(bool v) { _noxrebin = v; }

        //---------------------------------------------------------------------
        //! get no x-rebining flag
        bool no_x_rebinning() const { return _noxrebin; } 

        //---------------------------------------------------------------------
        //! perform normalization
        void normalization(bool v) { _norm = v; }

        //---------------------------------------------------------------------
        //! get normalization flag
        bool normalization() const { return _norm; }

        //---------------------------------------------------------------------
        virtual void operator()(const argument_type &data);

        //---------------------------------------------------------------------
        virtual std::ostream &stream_result(std::ostream &o) const;
};

