/*
 * MinOperation.hpp
 *
 *  Created on: Jun 14, 2011
 *      Author: eugen
 */

#ifndef MINOPERATION_HPP_
#define MINOPERATION_HPP_

template<typename T>
class MinOperation:public Operation{
private:
public:
	MinOperation():Operation(){}
	MinOperation(const Operation &o):Operation(o){}
	virtual ~MinOperation(){}

	virtual void run();

};

template<typename T> void MinOperation<T>::run(){
	Float128 result = 0;
	T &a = *((T *)(_input));
	const Shape &s = a.getShape();
	Index index;

	if (s.getRank() == 2) {
		index.setRank(s.getRank());
		//handle a 2D detector
		for (index[0] = _i_start; index[0] < _i_stop; index.increment(0)) {
			for (index[1] = _j_stop; index[1] < _j_stop; index.increment(1)) {
				if(result>a(index)) result = a(index);
			}
		}
	} else if (s.getRank() == 1) {
		index.setRank(s.getRank());
		//handle a 1D detector
		for(index[0]=_i_start;index[0]<_i_stop;index.increment(0)){
			if(result>a(index)) result = a(index);

		}
	}

	//if(_result != NULL ) delete _result;
	_result = (NumericObject *)(new Float128Scalar(result));
}


#endif /* MINOPERATION_HPP_ */
