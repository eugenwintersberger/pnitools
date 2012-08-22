/*
 * Exceptions.hpp
 *
 *  Created on: Sep 26, 2011
 *      Author: eugen
 */

#include<pni/utils/PNITypes.hpp>
#include<pni/utils/Exceptions.hpp>

using namespace pni::utils;

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

class CLIArgumentError:public Exception{
public:
	CLIArgumentError():Exception("CLIArgumentError"){}
	CLIArgumentError(const String &i,const String &d):Exception("CLIArgumentError",i,d){}
	virtual ~CLIArgumentError(){}

	friend std::ostream &operator<<(std::ostream &o,const CLIArgumentError &e);
};

class CLIOptionError:public Exception{
public:
	CLIOptionError():Exception("CLIOptionError"){}
	CLIOptionError(const String &i,const String &d):Exception("CLIOptionError",i,d){}
	virtual ~CLIOptionError(){}

	friend std::ostream &operator<<(std::ostream &o,const CLIOptionError &e);
};

class CLIError:public Exception{
public:
	CLIError():Exception("CLIError"){}
	CLIError(const String &i,const String &d):Exception("CLIError",i,d){}
	virtual ~CLIError(){}

	friend std::ostream &operator<<(std::ostream &o,const CLIError &e);
};

class FileTypeError:public Exception{
public:
	FileTypeError():Exception("FileTypeError"){}
	FileTypeError(const String &i,const String &d):Exception("FileTypeError",i,d){}
	virtual ~FileTypeError(){}

	friend std::ostream &operator<<(std::ostream &o,const FileTypeError &e);
};


#endif /* EXCEPTIONS_HPP_ */
