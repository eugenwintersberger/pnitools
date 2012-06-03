
#ifndef __SCALEOPERATOR_HPP__
#define __SCALEOPERATOR_HPP__

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/ArrayFactory.hpp>
#include <pni/utils/ArrayOperations.hpp>

#include "Operator.hpp"

using namespace pni::utils;

class ScaleOperator:public Operator
{
    private:
        size_t _center;  //center bin
        Float64 _delta;  //delta value
        Float64 _cvalue; //center value
        Float64Array _channels;
        Float64Array _data;
    public:
        ScaleOperator(const po::variables_map &config):
            Operator(config),
            _center(config["center"].as<size_t>()),
            _delta(config["delta"].as<Float64>()),
            _cvalue(config["cvalue"].as<Float64>())
        {}

        ~ScaleOperator(){}

        virtual void operator()(const Float64Array &channels,
                                const Float64Array &data)
        {
            _channels = Float64Array(channels);
            _data = Float64Array(data);

            for(Float64 &v: _channels)
            {
                v = _cvalue + _delta*(v - _center); 
            }
            
        }


        virtual std::ostream &stream_result(std::ostream &o) const
        {
            for(size_t i=0;i<_channels.size();i++)
            {
                o<<_channels[i]<<"\t"<<_data[i]<<std::endl;
            }
            return o;
        }
};

#endif
