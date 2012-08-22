/*
 * MaxOperation.hpp
 *
 *  Created on: Jun 14, 2011
 *      Author: eugen
 */

#include <pni/utils/Index.hpp>

#ifndef MAXOPERATION_HPP_
#define MAXOPERATION_HPP_

template<typename T>
class MaxOperation:public Operation{
private:
public:
	MaxOperation():Operation(){}
	MaxOperation(const Operation &o):Operation(o){}
	virtual ~MaxOperation(){}

	virtual void run();

};

template<typename T> void MaxOperation<T>::run(){
	Float128 result = 0;
	T &a = *((T *)(_input));
	const Shape &s = a.getShape();
	Index index;

	if (s.getRank() == 2) {
		index.setRank(s.getRank());
		//handle a 2D detector
		for (index[0] = _i_start; index[0] < _i_stop; index.increment(0)) {
			for (index[1] = _j_start; index[1] < _j_stop; index.increment(1)) {
				if(result<a(index)) result = a(index);
			}
		}
	} else if (s.getRank() == 1) {
		index.setRank(s.getRank());
		//handle a 1D detector
		for(index[0]=_i_start;index[0]<_i_stop;index.increment(0)){
			if(result<a(index)) result = a(index);

		}
	}

	//if(_result != NULL ) delete _result;
	_result = (NumericObject *)(new Float128Scalar(result));
}


#endif /* MAXOPERATION_HPP_ */
