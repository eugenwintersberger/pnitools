/*
 * ROI.hpp
 *
 *  Created on: May 31, 2011
 *      Author: eugen
 */

#ifndef ROI_HPP_
#define ROI_HPP_

#include <iostream>
#include <vector>
#include <pni/utils/PNITypes.hpp>
#include<boost/shared_ptr.hpp>
#include<boost/tokenizer.hpp>

using namespace pni::utils;

//ROIRange represents a single dimension in a ROI. It describes
//the start and stop channel of the ROI and holds a flag to
//decide whether or not this particular ROI is active.
class ROIRange{
protected:
	UInt64 _first;  //first channel
	UInt64 _last;   //last channel
	bool _active;               //determines whether or not the range is active
public:
	//default constructor
	ROIRange();
	//copy constructor
	ROIRange(const ROIRange &r);
	//standard constructor
	ROIRange(const UInt64 &first,const UInt64 last);
	//destructor
	virtual ~ROIRange();

	//set and get the first (starting) channel
	virtual void setFirst(const UInt64 first) { _first = first;}
	virtual UInt64 getFirst() const { return _first;}

	//set and get the last (stoppping) channel
	virtual void setLast(const UInt64 last) { _last = last;}
	virtual UInt64 getLast() const { return _last;}

	//set the ROI range active
	virtual void setActive() { _active = true;}
	//set the ROI range inactive
	virtual void setInActive() { _active = false; }
	//return activity status of the Range
	virtual bool isActive() const { return _active; }

	//overloaded assignment operator
	ROIRange &operator=(const ROIRange &r);

	//overloaded ouput operator
	friend std::ostream &operator<<(std::ostream &o,const ROIRange &r);

};

typedef std::vector<ROIRange> RangeList;

//a general N-dimensional region of interest (ROI)
class ROI{
protected:
	RangeList _ranges; //list of ROI ranges (one for each dimension)
public:
	ROI();
	ROI(const ROI &r);
	ROI(UInt64 ndims);
	virtual ~ROI();

	ROI &operator=(const ROI &r);
	ROIRange &operator[](UInt64 i);
	ROIRange operator[](UInt64 i) const;

	virtual void appendRange(const ROIRange &r);
	virtual UInt64 getDims() const;

	friend std::ostream &operator<<(std::ostream &o,const ROI &r);


};

typedef std::vector<ROI> ROIList;


#endif /* ROI_HPP_ */
