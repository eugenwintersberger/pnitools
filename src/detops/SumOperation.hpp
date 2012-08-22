/*
 * SumOperation.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: eugen
 */

#ifndef SUMOPERATION_HPP_
#define SUMOPERATION_HPP_

#include "Operation.hpp"
#include <pni/utils/Scalar.hpp>
#include <pni/utils/Index.hpp>

template<typename T>
class SumOperation:public Operation{
private:
public:
	SumOperation():Operation(){}
	SumOperation(const Operation &o):Operation(o){}
	virtual ~SumOperation(){}

	virtual void run();

};

template<typename T> void SumOperation<T>::run(){
	Float128 result = 0;
	T &a = *((T *)_input);
	const Shape &s = a.getShape();
	Index index;

	if (s.getRank() == 2) {
		index.setRank(s.getRank());
		//handle a 2D detector
		for (index[0] = _i_start; index[0] < _i_stop; index.increment(0)) {
			for (index[1] = _j_start; index[1] < _j_stop; index.increment(1)) {
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

	//if(_result != NULL ) delete _result;
	_result = (NumericObject *)(new Float128Scalar(result));
}




#endif /* SUMOPERATION_HPP_ */
