

#ifndef __SUMOPERATOR_HPP__
#define __SUMOPERATOR_HPP__

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/ArrayFactory.hpp>
#include <pni/utils/ArrayOperations.hpp>

#include "Operator.hpp"

using namespace pni::utils;

class SumOperator:public Operator
{
    private:
        Float64 _sum;
    public:
        SumOperator(const po::variables_map &config):
            Operator(config),
            _sum(0)
        {}

        ~SumOperator(){}

        virtual void operator()(const Float64Array &channels,
                                const Float64Array &data)
        {
            _sum = pni::utils::sum(data);
        }


        virtual std::ostream &stream_result(std::ostream &o) const
        {
            o<<_sum;
            return o;
        }
};

#endif
