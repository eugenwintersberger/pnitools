/*
 * Exceptions.cpp
 *
 *  Created on: Jun 14, 2011
 *      Author: Eugen Wintersberger
 */

#include "Exceptions.hpp"


FileTypeError::FileTypeError():Exception("FileTypeError"){
}


FileTypeError::FileTypeError(const String &i,const String &d)
			  :Exception("FileTypeError",i,d)
{
}

FileTypeError::~FileTypeError(){

}

std::ostream &operator<<(std::ostream &o,const FileTypeError &e){
	return e.print(o);
}

//======================================================================================
UnsupportedCommandError::UnsupportedCommandError():Exception("UnsupportedCommandError")
{
}



UnsupportedCommandError::UnsupportedCommandError(const String &i,const String &d)
:Exception("UnsupportedCommandError",i,d)
{
}

UnsupportedCommandError::~UnsupportedCommandError(){

}

std::ostream &operator<<(std::ostream &o,const UnsupportedCommandError &e){
	return e.print(o);
}
//======================================================================================

UnsupportedDataTypeError::UnsupportedDataTypeError():Exception("UnsupportedDataTypeError")
{
}

UnsupportedDataTypeError::UnsupportedDataTypeError(const String &i,const String &d)
:Exception("UnsupportedDataTypeError",i,d)
{
}

UnsupportedDataTypeError::~UnsupportedDataTypeError(){

}

std::ostream &operator<<(std::ostream &o,const UnsupportedDataTypeError &e){
	return e.print(o);
}

//======================================================================================
ROIRankError::ROIRankError():Exception("ROIRankError"){
}

ROIRankError::ROIRankError(const String &i,const String &d)
:Exception("ROIRankError",i,d){

}

ROIRankError::~ROIRankError(){

}

std::ostream &operator<<(std::ostream &o,const ROIRankError &e){
	return e.print(o);
}

//======================================================================================
ROIRangeError::ROIRangeError():Exception("ROIRangeError"){

}
ROIRangeError::ROIRangeError(const String &i,const String &d)
:Exception("ROIRangeError",i,d){

}

ROIRangeError::~ROIRangeError(){

}

std::ostream &operator<<(std::ostream &o,const ROIRangeError &e){
	return e.print(o);
}

NoInputError::NoInputError():Exception("NoInputError"){

}

NoInputError::NoInputError(const String &i,const String &d)
:Exception("NoInputError",i,d){

}

std::ostream &operator<<(std::ostream &o,const NoInputError &e){
	return e.print(o);
}
