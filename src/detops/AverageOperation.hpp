/*
 * AverageOperation.hpp
 *
 *  Created on: Jun 14, 2011
 *      Author: eugen
 */

#ifndef AVERAGEOPERATION_HPP_
#define AVERAGEOPERATION_HPP_

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/Index.hpp>

#include "Operation.hpp"

template<typename T>
class AverageOperation:public Operation{
private:
public:
	AverageOperation():Operation(){}
	AverageOperation(const Operation &o):Operation(o){}
	virtual ~AverageOperation(){}

	virtual void run();

};

template<typename T> void AverageOperation<T>::run(){
	Float128 result = 0;
	T &a = *((T *)_input);
	const Shape &s = a.getShape();
	Index index;

	if (s.getRank() == 2) {
		index.setRank(s.getRank());
		//handle a 2D detector
		for (index[0] = _i_start; index[0] < _i_stop; index.increment(0)) {
			for (index[1] = _j_start; index[1] < _j_stop; index.increment(0)) {
				result += a(index);
			}
		}
	} else if (s.getRank() == 1) {
		index.setRank(s.getRank());
		//handle a 1D detector
		for(index[0]=_i_start;index[0]<_i_stop;index.increment(0)){
			result += a(index);
		}
	}

	result /= s.getSize();

	//if(_result != NULL ) delete _result;
	_result = (NumericObject *)(new Float128Scalar(result));
}


#endif /* AVERAGEOPERATION_HPP_ */
