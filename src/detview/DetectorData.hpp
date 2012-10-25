#ifndef __DETECTORDATA_HPP__
#define __DETECTORDATA_HPP__

#include<algorithm>
#include<pni/utils/Types.hpp>
#include<pni/utils/Array.hpp>

#include<qwt-qt4/qwt_raster_data.h>

using namespace pni::utils;

class DetectorData : public QwtRasterData
{
    private:
        DArray<Float64> _data; //!< data array
        Float64 _min; //!< minimum value of the data
        Float64 _max; //!< maximum value of the data

    public:
        //! copy constructor
        DetectorData(const DetectorData &o);

        //! move constructor from array
        DetectorData(DArray<Float64> &&data);
    
        virtual QwtDoubleInterval range() const;

        virtual QwtRasterData *copy() const;

        virtual double value(double x,double y) const;
};
#endif
