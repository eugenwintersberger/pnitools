/*
 * ProgramConfig.hpp
 *
 *  Created on: May 31, 2011
 *      Author: eugen
 */

#ifndef DETINFOCONFIG_HPP_
#define DETINFOCONFIG_HPP_

#include <iostream>
#include <boost/program_options.hpp>
#include <pni/utils/PNITypes.hpp>


#include "../common/ProgramConfig.hpp"

//set an abriviation for the namespace
namespace popts = boost::program_options;
using namespace pni::utils;

class DetInfoConfig:public ProgramConfig {
protected:


	//Programm configuration cannot be copied
	DetInfoConfig(const DetInfoConfig &c){}
public:
	DetInfoConfig();
	virtual ~DetInfoConfig();


};

#endif /* DETINFOCONFIG_HPP_ */
