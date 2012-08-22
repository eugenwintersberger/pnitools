/*
 * Det2NxConfig.cpp
 *
 *  Created on: Sep 26, 2011
 *      Author: eugen
 */


#include "Det2NxConfig.hpp"

Det2NxConfig::Det2NxConfig():ProgramConfig() {
	// TODO Auto-generated constructor stub
	_odesc->add_options()
			("entry,e",popts::value<String>()->default_value(String("NXentry")),"Name of the Nexus NXentry")
			("instrument,i",popts::value<String>()->default_value("NXInstrument"),"Name of the NXinstrument")
			("detector,d",popts::value<String>()->default_value("NXDetector"),"Name of the detector")
			("compression,c",popts::value<String>()->default_value(String("none")),"Compression: none, deflate,lzf")
			("outfile,o",popts::value<String>()->default_value(String("out.nx.h5")),"Output file")
			("append","Append new data to existing data set")
			("replace","Replace the existing data with new data")
			("overwrite","overwrite existing output file")
			("split-size",popts::value<UInt64>()->default_value(0),"Split size for the data file!")
			;


}

Det2NxConfig::~Det2NxConfig() {
	// TODO Auto-generated destructor stub
}

String Det2NxConfig::getEntryName() const{
	String n = (*_vmap)["entry"].as<String>();
	return n;
}

String Det2NxConfig::getInstrumentName() const{
	String n = (*_vmap)["instrument"].as<String>();
	return n;
}

String Det2NxConfig::getDetectorName() const{
	String n = (*_vmap)["detector"].as<String>();
	return n;
}

String Det2NxConfig::getCompression() const{
	String n = (*_vmap)["compression"].as<String>();
	return n;
}

String Det2NxConfig::getOutputFile() const {
	String n = (*_vmap)["outfile"].as<String>();
	return n;
}

UInt64 Det2NxConfig::getSplitSize() const {
	return (*_vmap)["split-size"].as<UInt64>();
}

bool Det2NxConfig::getOverwrite() const {
	if(_vmap->count("overwrite")){
		return true;
	}else{
		return false;
	}
}

bool Det2NxConfig::getAppend() const {
	if(_vmap->count("append")){
		return true;
	}else{
		return false;
	}
}

bool Det2NxConfig::getReplace() const {
	if(_vmap->count("replace")){
		return true;
	}else{
		return false;
	}
}
