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
#include <pni/core/array_operations.hpp>

#include "operation.hpp"

using namespace pni::core;

/*!
\ingroup mcaops_devel
\brief scale operation implementation

This class implements the scale operation. Scaling means that the center
positions of the MCA bins are associated axis values. These values may represent
an energy or a time scale. 
To perform this operation basically two parameters are required 

\li a reference bin with an associated axis value
\li and a step size along the axis 

The reference bin will also be refered to as center bin throughout the
documentation. There are currently two strategies how to determine the center
bin

\li automatically, using the bin with the maximum count value
\li used defined, where the user passes the center bin manually

When the operator is called several sanity checks are performed on the input
data concerning the configuration of the class.
*/
class scale_operation:public operation
{
    private:
        
        bool _search_max;     //! determine center search mode
        size_t _center;       //! index of the center bin
        float64 _delta;       //! step size from bin to bin
        float64 _cvalue;      //! center bin value
        array_type _channels; //! output data bin values
        array_type _data;     //! output data values

        //---------------------------------------------------------------------
        /*!
        \brief check center bin value

        Check if the center bin value is within the channel number bounds of the
        input data. 

        \throws value_error if the center bin value is not within the interval
        \param channels the channel number array
        \param rec the exception record of the location where the check was
        performed
        */
        void check_channel_bounds(const array_type &channels,
                                  const exception_record &rec) const;

        //---------------------------------------------------------------------
        /*!
        \brief check the input arrays

        \throws size_mismatch_error if array sizes do not match
        \throws shape_mismatch_error in cases that the rank of one of the arrays
        is not 1
        \param channels array with channel data
        \param data array with MCA counter data
        \param rec the exception record of the function where this check
        function was called
        */
        void check_arrays(const array_type &channels, 
                          const array_type &data,const exception_record &rec)
            const;
    public:
        //---------------------------------------------------------------------
        //! default constructor
        scale_operation();

        //---------------------------------------------------------------------
        //! destructor
        ~scale_operation();

        //---------------------------------------------------------------------
        /*!
        \brief use maximum data for center bin

        If this is set to true the operation will use the bin with the maximum
        count value as center bin.
        \param v true or false
        */
        void use_data_maximum(bool v);

        bool use_data_maximum() const { return _search_max; }

        //---------------------------------------------------------------------
        //! get center bin
        size_t center_bin() const;
    
        //---------------------------------------------------------------------
        //! set center bin
        void center_bin(size_t b);

        //--------------------------------------------------------------------
        //! get center value
        float64 center_value() const;

        //---------------------------------------------------------------------
        //! set center value
        void center_value(float64 v);

        //---------------------------------------------------------------------
        //! get step size
        float64 delta() const;

        //---------------------------------------------------------------------
        //! set step size
        void delta(float64 d);
         

        //---------------------------------------------------------------------
        /*!
        \brief execute operation

        Perform the rescale operation on the input data provided by the
        arguments. The result is stored internally.
        \throws value_error if the center bin is out of the channel bounds
        \throws size_mismatch_error if channels and data size do not match
        \throws shape_mismatch_error if the rank of channels and size != 1
        \param channels input channels
        \param data input data
        */
        virtual void operator()(const array_type &channels,
                                const array_type &data);

        //---------------------------------------------------------------------
        //! write result to output stream
        virtual std::ostream &stream_result(std::ostream &o) const;
};

