/*
 * DetectorReader.cpp
 *
 *  Created on: Sep 27, 2011
 *      Author: eugen
 */

#include <cstdlib>
#include <cstdio>

#include <pni/utils/io/Reader.hpp>
#include <pni/utils/io/CBFReader.hpp>
#include <pni/utils/io/TIFFReader.hpp>

#include "DetectorReader.hpp"
#include "Exceptions.hpp"


DetectorReader::DetectorReader() {
	_data.reset();

}

DetectorReader::~DetectorReader() {
	_data.reset();
}

DetectorReader::DetectorReader(const DetectorReader &r){
	_data = r._data;
	_input_file = r._input_file;
}

void DetectorReader::_ext_to_lower(String &n){
	for(UInt32 i=0;i<n.size();i++){
		n[i] = tolower(n.c_str()[i]);
	}
}

void DetectorReader::setInputFile(const fs::path &file){
	_input_file = file;
}

void DetectorReader::operator()(){
	EXCEPTION_SETUP("void DetectorReader::operator()()");
	Reader *reader = NULL;

	if(!fs::is_regular_file(_input_file)){
		//raise an exception here
	}

	if(!fs::exists(_input_file)){
		//raise an exception here
	}

	//obtain the extension of a file
	String n = _input_file.extension();
	_ext_to_lower(n);

	if(n == ".tif"){
		reader = (Reader *)(new TIFFReader());
	}else if (n == ".cbf"){
		reader = (Reader *)(new CBFReader());
	}else{
		EXCEPTION_INIT(FileTypeError,"File type not supported!");
		EXCEPTION_THROW();
	}


	reader->setFileName(_input_file.string());
	reader->open();
	_data = boost::dynamic_pointer_cast<ArrayObject>(reader->read());
	reader->close();

	/*/
	 * stack.lock();
	 * stack.push(_data);
	 * stack.unlock();
	 *
	 */

	if(reader != NULL) delete reader;
}

