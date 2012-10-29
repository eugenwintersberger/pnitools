#include "IntensityRange.hpp"

//-----------------------------------------------------------------------------
void IntensityRange::_set_minmax(const DetectorData &d)
{
    typedef DetectorData::storage_type data_t;
    const data_t &data = d.getData();

    _max = *(std::max_element(data.begin(),data.end()));
    _min = *(std::min_element(data.begin(),data.end()));
}

//-----------------------------------------------------------------------------
IntensityRange::IntensityRange():_min(0.),_max(0)
{}

//-----------------------------------------------------------------------------
IntensityRange::IntensityRange(Float64 min,Float64 max):
    _min(min),
    _max(max)
{}

//-----------------------------------------------------------------------------
IntensityRange::IntensityRange(const DetectorData &d)
{
    _set_minmax(d);
}
//-----------------------------------------------------------------------------
void IntensityRange::setMin(Float64 value)
{
    if(value>_max)
    {
        std::cerr<<"minimum value must not be larger than maximum"<<std::endl;
    }
    else
    {
        _max = value;
        emit rangeChanged(_min,_max);
    }
}

//-----------------------------------------------------------------------------
void IntensityRange::set(const DetectorData &d)
{
    _set_minmax(d);
    emit rangeChanged(_min,_max);
}

//-----------------------------------------------------------------------------
void IntensityRange::setMax(Float64 value)
{
    if(value<_min)
    {
        std::cerr<<"maximum value must not be small than minimum"<<std::endl;
    }
    else
    {
        _min = value;
        emit rangeChanged(_min,_max);
    }
}

//-----------------------------------------------------------------------------
void IntensityRange::dataChanged(const DetectorData &d)
{
    _set_minmax(d);
    emit rangeChanged(_min,_max);
}

//-----------------------------------------------------------------------------
Float64 IntensityRange::getMin() const
{
    return _min;
}

//-----------------------------------------------------------------------------
Float64 IntensityRange::getMax() const
{
    return _max;
}

