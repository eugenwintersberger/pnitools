/*
 * DetectorReader.hpp
 *
 *  Created on: Sep 27, 2011
 *      Author: eugen
 */

#ifndef DETECTORREADER_HPP_
#define DETECTORREADER_HPP_

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/ArrayObject.hpp>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
using namespace pni::utils;

class DetectorReader {
private:
	ArrayObject::sptr _data;
	fs::path _input_file;

	void _ext_to_lower(String &e);
public:
	DetectorReader();
	DetectorReader(const DetectorReader &r);
	virtual ~DetectorReader();

	virtual void setInputFile(const fs::path &ifile);
	void operator()();
	ArrayObject::sptr getData(){
		return _data;
	}
};

#endif /* DETECTORREADER_HPP_ */
