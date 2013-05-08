/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: 03.06.2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/darray.hpp>
#include <pni/core/array_operations.hpp>

#include "operation.hpp"

using namespace pni::core;

/*!
\ingroup mcaops_devel
\brief implementation of rebining

This class provides the implementation of the rebining operation for MCA
histograms. 

*/
class rebin_operation:public operation
{
    private:
        //! number of bins to collate
        size_t _bsize; 
        //! flag for not rebining the x-axis
        bool   _noxrebin;
        //! flag for normalization
        bool   _norm;
        //! output channel data
        array_type _channels;
        //! output mca data
        array_type _data;
    public:
        //---------------------------------------------------------------------
        //! default constructor
        rebin_operation();

        //---------------------------------------------------------------------
        //! destructor
        ~rebin_operation(){}

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
        //! perform normalization
        void do_normalization(bool v) { _norm = v; }


        //---------------------------------------------------------------------
        virtual void operator()(const array_type &channels,
                                const array_type &data);

        //---------------------------------------------------------------------
        virtual std::ostream &stream_result(std::ostream &o) const;
};

