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
#include <boost/tokenizer.hpp>


#include "ROI.hpp"

//set an abriviation for the namespace
namespace popts = boost::program_options;

class ProgramConfig {
protected:
	popts::variables_map *_vmap;
	popts::options_description *_odesc;
	popts::positional_options_description *_oargs;

	//Programm configuration cannot be copied
	ProgramConfig(const ProgramConfig &c){}

	//some typedefs for the tokenizer system to parse ROI strings
	typedef boost::tokenizer<boost::char_separator<char> > roi_tokenizer;
	typedef roi_tokenizer::iterator roi_token_iterator;
	typedef boost::char_separator<char> roi_separator;
public:
	typedef std::vector<pni::utils::String> InputFileList;
	typedef InputFileList::iterator InputFileIterator;
	ProgramConfig();
	virtual ~ProgramConfig();

	virtual void parse(int argc,char **argv);
	virtual int help() const;
	virtual std::string getMask() const;
	virtual std::string getCommand() const;
	virtual std::string getBackground() const;
	virtual std::string getInputFormat() const;
	virtual void setROIList(ROIList &rl) const;
	virtual double getNorm() const;
	virtual double getExposure() const;
	virtual InputFileList *getInputFileList() const;
	virtual bool isVerbose() const;
	virtual bool printFileNames() const;


};

#endif /* PROGRAMCONFIG_HPP_ */
