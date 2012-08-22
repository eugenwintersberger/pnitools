/*
 * ROIRange.cpp
 *
 *  Created on: Jun 15, 2011
 *      Author: Eugen Wintersberger
 */

#include <iostream>

#include "ROI.hpp"

ROIRange::ROIRange(){
	_first = 0;
	_last = 0;
	_active = false;
}

ROIRange::ROIRange(const ROIRange &r){
	_first = r._first;
	_last = r._last;
	_active = r._active;
}

ROIRange::ROIRange(const pni::utils::UInt64 &first,const pni::utils::UInt64 last){
	_first = first;
	_last = last;
	_active = true;
}

ROIRange::~ROIRange(){
	_first = 0;
	_last = 0;
	_active = false;
}

ROIRange &ROIRange::operator=(const ROIRange &r){
	if(this != &r){
		_first = r._first;
		_last = r._last;
		_active = r._active;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o,const ROIRange &r){
	o<<"ROI-Range: "<<r._first<<" - "<<r._last<<" active = "<<r._active;
	return o;
}
