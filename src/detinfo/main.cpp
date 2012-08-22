/*
 * main.cpp
 *
 *  Created on: Sep 26, 2011
 *      Author: Eugen Wintersberger
 */

#include<iostream>

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/io/CBFReader.hpp>
#include <pni/utils/io/TIFFReader.hpp>
#include <boost/filesystem.hpp>

#include "DetInfoConfig.hpp"
#include "../common/Exceptions.hpp"

using namespace pni::utils;
namespace fs = boost::filesystem;

int main(int argc,char **argv)
{
	DetInfoConfig conf;
	DetInfoConfig::InputFileList *iflist = NULL;
	DetInfoConfig::InputFileIterator ifiter;
	ArrayObject::sptr a;
	Reader *reader = NULL;

    //print help message and abort 
	if(argc<2)
    {
		std::cerr<<"Usage: detinfo [program options] FILE ..."<<std::endl;
		return 1;
	}


	//parse program options
	conf.parse(argc,argv);

	//show helptext and exit
	if(conf.help()) return 0;

	//get list of input files
	try
    {
		iflist = conf.getInputFileList();
	}
    catch(...)
    {
		return 1;
	}

	//loop over all input files
	UInt64 n_proc_files = 0; //number of processed files
	UInt64 n_nopr_files = 0; //number of objects in the file system not processed

	for(ifiter = iflist->begin(); ifiter != iflist->end(); ++ifiter)
    {
		//do some checks on the filename passed to the program
		fs::path &file = *ifiter;

		//check if path exists
		if(!fs::exists(file)){
			std::cerr<<"File "<<file<<" does not exist!"<<std::endl;
			n_nopr_files++;
			continue;
		}

		//check if the path object is a regular file
		if(!fs::is_regular_file(file)){
			std::cerr<<"File "<<file<<" is not a file!"<<std::endl;
			n_nopr_files++;
			continue;
		}

		//now we have to choose the proper reader
		String ext = file.extension();
		if(ext == ".cbf"){
			reader = (Reader *)(new CBFReader());
		}else if(ext == ".tif"){
			reader = (Reader *)(new TIFFReader());
		}else{
			//raise an exception here and finish the program
			if(iflist != NULL) delete iflist;
		}

		reader->setFileName(file.string());
		reader->open();
		a = boost::dynamic_pointer_cast<ArrayObject>(reader->read());
		if(a!=NULL){
			const Shape &s = a->getShape();
			std::cout<<file.filename()<<":  "<<s<<std::endl;
		}

		//increment counter for processed files
		n_proc_files++;
		a.reset();
		if(reader != NULL)
        {
			delete reader;
			reader = NULL;
		}
	}

	//free memory
	if(iflist != NULL) delete iflist;
	a.reset();
	if(reader != NULL) delete reader;

	return 0;
}


