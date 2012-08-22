/*
 * Operations.hpp
 *
 *  Created on: Jun 7, 2011
 *      Author: eugen
 */

#ifndef OPERATIONS_HPP_
#define OPERATIONS_HPP_

#include <pni/utils/DataObject.hpp>
#include <pni/utils/PNITypes.hpp>
#include <pni/utils/ArrayShape.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/Exceptions.hpp>

#include "ROI.hpp"

using namespace pni::utils;

class Operation{
protected:
	ArrayObject* _input;
	NumericObject* _result;

	//start stop indices for array operations
	UInt64 _i_start;
	UInt64 _i_stop;
	UInt64 _j_start;
	UInt64 _j_stop;
	Operation(const Operation &){}

	//some protected functions
	void _check_roi(const ROI &r);
public:
	Operation();
	virtual ~Operation();

	virtual void setInputData(ArrayObject* o);
	virtual void applyROI(const ROI &roi);
	virtual void resetROI();
	virtual void resetResult(){
		_result = NULL;
	}
	virtual NumericObject* getResult();

	virtual void operator()();
	virtual void run(){
		std::cerr<<"Run base class method!"<<std::endl;
	}

	virtual void run(const ROI &roi){

	}


};





#endif /* OPERATIONS_HPP_ */
