#ifndef __INTENSITYRANGE_HPP__
#define __INTENSITYRANGE_HPP__

#include<QtCore>

#include<pni/utils/Types.hpp>

#include "DetectorData.hpp"

using namespace pni::utils;

class IntensityRange:public QObject
{
    Q_OBJECT
    private:
        Float64 _min; //!< minimum value 
        Float64 _max; //!< maximum value

        void _set_minmax(const DetectorData &d);
    signals:
        void rangeChanged(Float64 min,Float64 max);
    public slots:
        void dataChanged(const DetectorData &d);
    public:
        //============================constructors=============================
        IntensityRange();

        //-------
        IntensityRange(Float64 min,Float64 max);

        IntensityRange(const DetectorData &d);
        

        //---------------------------------------------------------------------
        /*! 
        \brief set the minimum of the plot range

        Sets the minimum of the plot range. This method emits the rangeChanged
        signal.
        \param value the new minimum value
        */
        void setMin(Float64 value);

        //---------------------------------------------------------------------
        /*!
        \brief set maximum value

        Sets the maximum value of the plot range. This method emits the
        rangeChanged signal. 
        */
        void setMax(Float64 value);

        //---------------------------------------------------------------------
        /*!
        \brief set minimum and maximum 

        Set minimum and maximum from an instance of DetectorData. This member
        function emits the rangeChanged signal.
        \param d instance of DetectorData
        */
        void set(const DetectorData &d);

        //---------------------------------------------------------------------
        //! return minimum
        Float64 getMin() const;

        //---------------------------------------------------------------------
        //! return maximum
        Float64 getMax() const;
};

#endif
