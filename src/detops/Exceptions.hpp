/*
 * Exceptions.hpp
 *
 *  Created on: Jun 14, 2011
 *      Author: eugen
 */

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

#include <iostream>

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/Exceptions.hpp>

using namespace pni::utils;

//raised if the file format is not supported
class FileTypeError:public Exception{
public:
	FileTypeError();
	FileTypeError(const String &i,const String &d);
	virtual ~FileTypeError();

	friend std::ostream &operator<<(std::ostream &o,const FileTypeError &e);
};

//raised if the command string is not supported
class UnsupportedCommandError:public Exception {
public:
	UnsupportedCommandError();
	UnsupportedCommandError(const String &i,const String &d);
	virtual ~UnsupportedCommandError();

	friend std::ostream &operator<<(std::ostream &o,const UnsupportedCommandError &e);
};

//raised if the array returned by the reader is of an unsupported type
class UnsupportedDataTypeError:public Exception{
protected:
	TypeID _tid;
public:
	UnsupportedDataTypeError();
	UnsupportedDataTypeError(const String &i,const String &d);
	virtual ~UnsupportedDataTypeError();

	friend std::ostream &operator<<(std::ostream &o,const UnsupportedDataTypeError &e);
};

//raised if the range of the ROI does not fit into the shape of a detector array.
class ROIRankError:public Exception{
public:
	ROIRankError();
	ROIRankError(const String &i,const String &d);
	virtual ~ROIRankError();

	friend std::ostream &operator<<(std::ostream &o,const ROIRankError &e);
};

//raised if the ranges of a ROI and the array dimension do not match
class ROIRangeError:public Exception{
public:
	ROIRangeError();
	ROIRangeError(const String &i,const String &d);
	virtual ~ROIRangeError();

	friend std::ostream &operator<<(std::ostream &o,const ROIRangeError &e);

};
class NoInputError:public Exception{
public:
	NoInputError();
	NoInputError(const String &i,const String &d);
	virtual ~NoInputError(){}

	friend std::ostream &operator<<(std::ostream &o,const NoInputError &e);
};



#endif /* EXCEPTIONS_HPP_ */
