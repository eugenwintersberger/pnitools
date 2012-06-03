
#ifndef __MAXOPERATOR_HPP__
#define __MAXOPERATOR_HPP__

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/ArrayFactory.hpp>
#include <pni/utils/ArrayOperations.hpp>

#include "Operator.hpp"

using namespace pni::utils;

class MaxOperator:public Operator
{
    private:
        size_t _max_pos;
        Float64 _max_value;
    public:
        MaxOperator(const po::variables_map &config):
            Operator(config),
            _max_pos(0),
            _max_value(0)
        {}

        ~MaxOperator(){}

        virtual void operator()(const Float64Array &channels,
                                const Float64Array &data)
        {
            _max_pos = pni::utils::max_offset(data);
            _max_value = data[_max_pos];
        }

        virtual std::ostream &stream_result(std::ostream &o) const
        {
            o<<_max_pos<<"\t"<<_max_value;
            return o;
        }
};

#endif
