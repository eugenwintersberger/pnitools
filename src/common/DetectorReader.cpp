/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * pnitools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pnitools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Sep 27, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
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

