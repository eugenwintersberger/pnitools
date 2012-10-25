
#include "DetectorData.hpp"

//-----------------------------------------------------------------------------
DetectorData::DetectorData(const DetectorData &o):
              QwtRasterData(o),
              _data(o._data), 
              _min(o._min), 
              _max(o._max)
{
    auto s = _data.shape<shape_t>();
    setBoundingRect(QwtDoubleRect(0.,0.,double(s[0]-1),double(s[1]-1)));
}

//-----------------------------------------------------------------------------
DetectorData::DetectorData(DArray<Float64> &&data):
              QwtRasterData(),
              _data(std::move(data))
{
    _min = *(std::min_element(_data.begin(),_data.end()));
    _max = *(std::max_element(_data.begin(),_data.end()));

    auto s = _data.shape<shape_t>();
    setBoundingRect(QwtDoubleRect(0.,0.,double(s[0]-1),double(s[1]-1)));
}

//-----------------------------------------------------------------------------
QwtDoubleInterval DetectorData::range() const
{
    return QwtDoubleInterval(_min,_max);
}

//-----------------------------------------------------------------------------
QwtRasterData *DetectorData::copy() const
{
    return new DetectorData(*this);
}

//-----------------------------------------------------------------------------
double DetectorData::value(double x,double y) const
{
    double value;
    try
    {
        size_t i = size_t(x);
        size_t j = size_t(y);

        value = _data(i,j);
    }
    catch(IndexError &error)
    {
        size_t i = size_t(x);
        size_t j = size_t(y);
        std::cerr<<"Position is: "<<x<<","<<y<<std::endl;
        std::cerr<<"Index is ("<<i<<","<<j<<")"<<std::endl;
        std::cerr<<"Shape is ";
        auto s = _data.shape<shape_t>();
        for(auto d: s) std::cerr<<d<<" ";
        std::cerr<<std::endl;
        std::cerr<<error<<std::endl;
        error.append(EXCEPTION_RECORD);
        throw error;
    }
    return value;
}
