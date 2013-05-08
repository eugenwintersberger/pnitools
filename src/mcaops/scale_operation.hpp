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
\ingroup mcaops_classes
\brief scale operation implementation

This class implements the scale operation. Scaling means that the center
positions of the MCA bins are associated with time values. 
In order to do this one has to provide a center bin and a time value associated
with it. An additional temporal step size then determines the time values for
all other bins. 
There are currently two strategies how to determine the center bin of the input
data

\li automatically, using the bin with the maximum count value
\li used defined, where the user passes the center bin manually

*/
class scale_operation:public operation
{
    private:
        //! determine center search mode
        bool _search_max; 
        //! index of the center bin
        size_t _center;  
        //! step size from bin to bin
        float64 _delta;  
        //! center bin value
        float64 _cvalue; 
        //! output data bin values
        array_type _channels;
        //! output data values
        array_type _data;
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
        \param channels input channels
        \param data input data
        */
        virtual void operator()(const array_type &channels,
                                const array_type &data);

        //---------------------------------------------------------------------
        //! write result to output stream
        virtual std::ostream &stream_result(std::ostream &o) const;
};

