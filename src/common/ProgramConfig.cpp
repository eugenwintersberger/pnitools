/*
 * ProgramConfig.cpp
 *
 *  Created on: May 31, 2011
 *      Author: eugen
 */

#include<string>
#include<vector>
#include<cstdio>
#include<cstdlib>

#include "ProgramConfig.hpp"
#include "Exceptions.hpp"

ProgramConfig::ProgramConfig() {
	_vmap = new popts::variables_map();
	_odesc = new popts::options_description("Programm options");

	//set command line options
	_odesc->add_options()
			("help,h","print help message")
			("verbose,v","print verbose text during processing")
			("iformat",popts::value<String>(),"input format")
			("input-files",popts::value<StringList>(),"input files")
			("template,t",popts::value<String>(),"file template")
			("path,p",popts::value<String>()->default_value(String(".")) ,"file path")//needs a default value
			;


	_oargs = new popts::positional_options_description();
	_oargs->add("input-files",-1);
}

ProgramConfig::~ProgramConfig() {
	if (_vmap != NULL) delete _vmap;
	if (_odesc != NULL) delete _odesc;
	if (_oargs != NULL) delete _oargs;
}

void ProgramConfig::parse(int argc,char **argv){
	popts::store(popts::command_line_parser(argc,argv).options(*_odesc).positional(*_oargs).run(),*_vmap);
	popts::notify(*_vmap);
}

int ProgramConfig::help() const {
	if (_vmap->count("help")) {
		std::cout << *_odesc << std::endl;
		return 1;
	}
	return 0;
}

String ProgramConfig::getInputFormat() const {
	if(_vmap->count("iformat")){
		return (*_vmap)["iformat"].as<std::string>();
	}else{
		return String("cbf");
	}
}



ProgramConfig::InputFileList *ProgramConfig::getInputFileList() const{
	EXCEPTION_SETUP("ProgramConfig::InputFileList *ProgramConfig::getInputFileList() const");
	ProgramConfig::InputFileList *l = new ProgramConfig::InputFileList;
	char buffer[1024];
	fs::path root_path((*_vmap)["path"].as<String>()); //get the root path

	if(_vmap->count("template")){
		//a file template was passed to the program in this case the
		//three arguments following the program options are interpreted as follows
		// start stop inc
		if(!_vmap->count("input-files")){
			EXCEPTION_INIT(CLIArgumentError,"Using -t requires three arguments for the file numbers!");
			EXCEPTION_THROW();
		}


		String t = (*_vmap)["template"].as<String>();
		std::cout<<t.size()<<std::endl;
		if(t.size()==0){
			EXCEPTION_INIT(CLIOptionError,"The filename format string must not contain more than one numeric placeholder!");
			EXCEPTION_THROW();
		}

		StringList tmplist = (*_vmap)["input-files"].as<StringList>();
		if((tmplist.size()%3)!=0){
			EXCEPTION_INIT(CLIArgumentError,"Number of arguments must be an integer multiple of 3!");
			EXCEPTION_THROW();
		}

		//loop over all blocks
		for(UInt32 b=0;b<tmplist.size()/3;b++){
			UInt64 start = (UInt64)atoi(tmplist[b*3].c_str());
			UInt64 stop = (UInt64)atoi(tmplist[b*3+1].c_str());
			UInt64 inc = (UInt64)atoi(tmplist[b*3+2].c_str());

			//assemble filenames and concatenate them with a root path
			//if necessary (if the filenames themselfes are not absolute)
			for(UInt64 i=start;i<=stop;i+=inc){
				sprintf(buffer,t.c_str(),i);  //create the file name
				fs::path filepath(buffer);

				//need to find out whether or not the file name is an absolute path
				//in this case the -p (--path) option must be ignored
				if(filepath.is_complete()){
					l->push_back(filepath);
				}else{
					fs::path apath(root_path);
					apath /= filepath;
					l->push_back(apath);
				}
			}
		}
	}else if(_vmap->count("input-files")){
		//fetch the list of strings with file names from the argument list
		StringList tmplist = (*_vmap)["input-files"].as<StringList>();
		StringList::iterator iter;
		for(iter = tmplist.begin();iter!=tmplist.end();iter++){
			fs::path filename((*iter).c_str());
			if(filename.is_complete()){
				l->push_back(filename);
			}else{
				fs::path apath(root_path);
				apath /= filename;
				l->push_back(apath);
			}
		}
	}else{
		EXCEPTION_INIT(CLIError,"Cannot create list of input files!");
		EXCEPTION_THROW();
	}

	return l;
}

bool ProgramConfig::isVerbose() const {
	if (_vmap->count("verbose")){
		return true;
	}else{
		return false;
	}
}

