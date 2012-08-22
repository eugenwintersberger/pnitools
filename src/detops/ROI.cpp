/*
 * ROI.cpp
 *
 *  Created on: Jun 15, 2011
 *      Author: Eugen Wintersberger
 */

#include <iostream>

#include "ROI.hpp"

ROI::ROI(){

}

ROI::ROI(const ROI &r){
	_ranges = r._ranges;
}

ROI::ROI(UInt64 ndims){
	_ranges = RangeList(ndims);
}

ROI::~ROI(){

}

ROI &ROI::operator=(const ROI &r){
	if(this != &r){
		_ranges = r._ranges;
	}
	return *this;
}

ROIRange &ROI::operator[](UInt64 i){
	return _ranges[i];
}

ROIRange ROI::operator[](UInt64 i) const{
	return _ranges[i];
}

void ROI::appendRange(const ROIRange &r){
	_ranges.push_back(r);
}

UInt64 ROI::getDims() const{
	return _ranges.size();
}

std::ostream &operator<<(std::ostream &o,const ROI &r){
	o<<r._ranges.size()<<" - dimensional ROI"<<std::endl;

	for(UInt64 i=0;i<r.getDims();i++){
		o<<r[i]<<std::endl;
	}

	return o;
}
