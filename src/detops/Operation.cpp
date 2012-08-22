/*
 * Operations.cpp
 *
 *  Created on: Jun 7, 2011
 *      Author: eugen
 */

#include <pni/utils/Array.hpp>

#include "Operation.hpp"
#include "Exceptions.hpp"

Operation::Operation(){
	_input = NULL;
	_result = NULL;
	_i_start = 0;
	_i_stop = 0;
	_j_start = 0;
	_j_stop = 0;
}

Operation::~Operation(){
	_input = NULL;
	_result = NULL;
}

void Operation::setInputData(ArrayObject* o){
	EXCEPTION_SETUP("void Operation::setInputData(ArrayObject* o)");
	_input = o;
	const Shape &s = _input->getShape();

	//reset loop ranges to the native array values
	if (s.getRank() == 1) {
		_i_start = 0;
		_i_stop = s[0];
	} else if (s.getRank() == 2) {
		_i_start = 0;
		_i_stop = s[0];
		_j_start = 0;
		_j_stop = s[1];
	}
}


void Operation::applyROI(const ROI &roi){
	EXCEPTION_SETUP("void Operation::applyROI(const ROI &roi)");

	if(_input==NULL){
		EXCEPTION_INIT(NoInputError,"No input has been associated with the operation!");
		EXCEPTION_THROW();
	}
	//check if the ROI works for the given input data
	_check_roi(roi);

	if(roi.getDims()==1){
		_i_start = roi[0].getFirst();
		_i_stop = roi[0].getLast();
	}else if (roi.getDims()==2){
		_i_start = roi[0].getFirst();
		_i_stop  = roi[0].getLast();
		_j_start = roi[1].getFirst();
		_j_stop  = roi[1].getLast();
	}
}

void Operation::resetROI(){
	EXCEPTION_SETUP("void Operation::resetROI()");

	if(_input==NULL){
		EXCEPTION_INIT(NoInputError,"No input has been associated with the operation!");
		EXCEPTION_THROW();
	}

	const Shape &s = _input->getShape();

	//reset loop ranges to the native array values
	if(s.getRank()==1){
		_i_start = 0;
		_i_stop = s[0];
	}else if (s.getRank()==2){
		_i_start = 0;
		_i_stop = s[0];
		_j_start = 0;
		_j_stop = s[1];
	}
}

NumericObject* Operation::getResult(){
	return _result;
}

void Operation::operator()(){

}

void Operation::_check_roi(const ROI &roi){
	EXCEPTION_SETUP("void Operation::_check_roi(const ROI &roi)");
	const Shape &s = _input->getShape();

	//check if the ranks of ROI and input data fit
	if(roi.getDims()!=s.getRank()){
		EXCEPTION_INIT(ROIRankError,"Rank of input data and ROI do not match!");
		EXCEPTION_THROW();
	}

	//check if the extents of ROI and
	for(UInt64 i=0;i<roi.getDims();i++){
		const ROIRange &r = roi[i];
		if((r.getLast()>s[i])||(r.getFirst()>s[i])){
			EXCEPTION_INIT(ROIRangeError,"ROI range does not fit into data dimension!");
			EXCEPTION_THROW();
		}
	}

}



