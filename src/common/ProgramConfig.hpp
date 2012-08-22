/*
 * ProgramConfig.hpp
 *
 *  Created on: May 31, 2011
 *      Author: eugen
 */

#ifndef PROGRAMCONFIG_HPP_
#define PROGRAMCONFIG_HPP_

#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <pni/utils/PNITypes.hpp>

//set an abriviation for the namespace
namespace popts = boost::program_options;
namespace fs = boost::filesystem;
using namespace pni::utils;

class ProgramConfig {
protected:
	popts::variables_map *_vmap;
	popts::options_description *_odesc;
	popts::positional_options_description *_oargs;

	typedef std::vector<String> StringList; //internal data type for arguments

	//Programm configuration cannot be copied
	ProgramConfig(const ProgramConfig &c){}
public:
	typedef std::vector<fs::path> InputFileList;
	typedef InputFileList::iterator InputFileIterator;
	ProgramConfig();
	virtual ~ProgramConfig();


	virtual String getInputFormat() const;
	virtual void parse(int argc,char **argv);
	virtual int help() const;
	virtual InputFileList *getInputFileList() const;
	virtual bool isVerbose() const;


};

#endif /* PROGRAMCONFIG_HPP_ */
