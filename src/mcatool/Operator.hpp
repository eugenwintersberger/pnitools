
#ifndef __OPERATOR_HPP__
#define __OPERATOR_HPP__

#include <iostream>
#include<boost/program_options/variables_map.hpp>
#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/ArrayFactory.hpp>

using namespace pni::utils;
namespace po = boost::program_options;

class Operator
{
    public:
        Operator(const po::variables_map &config){}
        virtual ~Operator() {}

        virtual void operator()(const Float64Array &channels,
                        const Float64Array &data) = 0;

        virtual std::ostream &stream_result(std::ostream &o) const = 0;
};

std::ostream &operator<<(std::ostream &o,const Operator &op)
{
    return op.stream_result(o);
}

#endif
