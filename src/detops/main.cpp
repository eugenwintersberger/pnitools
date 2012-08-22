/*
 * main.cpp
 *
 *  Created on: May 31, 2011
 *      Author: Eugen Wintersberger
 */

#include <iostream>
#include <typeinfo>
#include <boost/filesystem.hpp>
#include <pni/utils/PNITypes.hpp>
#include <pni/utils/io/CBFReader.hpp>
#include <pni/utils/io/TIFFReader.hpp>
#include <pni/utils/Array.hpp>

#include "ProgramConfig.hpp"
#include "ROI.hpp"
#include "Operation.hpp"
#include "OperationDispatcher.hpp"
#include "Exceptions.hpp"

//set namespace shortcut for boost::filesystem
namespace fs = boost::filesystem;
using namespace pni::utils;

int main(int argc, char **argv) {
	ProgramConfig conf; //global program configuration
	ProgramConfig::InputFileList *il; //list with input files
	ProgramConfig::InputFileIterator ifiter; //iterator over the input file list
	ROIList rois; //ROI
	String command; //string with the command to execute
	String mask_file; //name of a mask file
	String bg_file; //name of a background file
	OperationDispatcher  OpsDispatch; //operator class with array operations
	ArrayObject::sptr array; //pointer to an array object
	NumericObject* result;

	//parse command line arguments
	conf.parse(argc, argv);
	//if the use requrested the help messages - print help text and
	//exit program
	if (conf.help()) return 0;

	//get mask file name
	mask_file = conf.getMask();
	//get background file name
	bg_file = conf.getBackground();
	//get the command to execute
	command = conf.getCommand();

	//print some configuration details if ouput is set to verbose
	if (conf.isVerbose()) {
		std::cout << "Command:         " << command << std::endl;
		std::cout << "Background file: " << bg_file << std::endl;
		std::cout << "Mask file:       " << mask_file << std::endl;
		std::cout << "Norm:            " << conf.getNorm() << std::endl;
		std::cout << "Exposure:        " << conf.getExposure() << std::endl;
	}

	conf.setROIList(rois);
	if ((!rois.empty())&&(conf.isVerbose())) {
		ROIList::iterator iter;
		for(iter = rois.begin();iter!=rois.end();iter++){
			std::cout<<*iter<<std::endl;
		}
	}

	//fetch the list of input files from the configuration object
	//if no file is given print an error message and abort the program
	il = conf.getInputFileList();
	if (il == NULL) {
		std::cerr << "No input files are where passed to the Program!"
				<< std::endl;
		return -1;
	}

	//main loop - loop over all input files
	for (ifiter = il->begin(); ifiter != il->end(); ++ifiter) {
		if (conf.isVerbose()) {
			std::cout << "processing file: " << *ifiter << std::endl;
		}

		//create a path object for further processing
		fs::path ifpath(*ifiter);

		//need to check here whether or not the input file exists
		//if not - preceed to the next file and print an error message
		if (!fs::exists(ifpath)) {
			std::cerr << "file or directory " << *ifiter << " does not exist!"
					<< std::endl;
			//if the file or directory does not exist: continue with the next file
			continue;
		}

		if (!fs::is_regular_file(ifpath)) {
			std::cerr << *ifiter << " is not a regular file!" << std::endl;
			//if the object is not a regular file - continue with the next file
			continue;
		}

		//determine the file type and create the appropriate reader
		//actually this is done only be checking the file extension (not very save
		//but should work for the first release)
		pni::utils::String ifextension(ifpath.extension());
		if (ifextension == ".cbf") {
			//start here with real operations
			pni::utils::CBFReader *reader;
			reader = new pni::utils::CBFReader();
			reader->setFileName(*ifiter);
			reader->open();
			array = boost::dynamic_pointer_cast<ArrayObject>(reader->read());
			reader->close();
			delete reader;
		}else if ((ifextension == ".tif")||(ifextension == ".tiff")){
			pni::utils::TIFFReader *reader;
			reader = new pni::utils::TIFFReader();

			reader->setFileName(*ifiter);
			reader->open();
			array = boost::dynamic_pointer_cast<ArrayObject>(reader->read());
			reader->close();
			delete reader;
		}else if ((ifextension == ".spe")) {
			std::cerr<<"not implemented yet!"<<std::endl;
		} else {
			std::cerr << "file " << *ifiter << " is of unknow file format!"
					<< std::endl;
			std::cerr<<"aborting program!"<<std::endl;
			return -1;
			continue;
		}

		if(conf.printFileNames()){
			std::cout<<*ifiter<<": ";
		}

		//check if the operation requested by the user is supported

		Operation *op = NULL;
		try {
			op = OpsDispatch.getOperation(command, array->getTypeID());
		} catch (UnsupportedCommandError &e) {
			std::cerr << e << std::endl;
			std::cerr << "abort program!" << std::endl;
			return -1;
		} catch (UnsupportedDataTypeError &e) {
			std::cerr << e << std::endl;
			std::cerr << "abort program!" << std::endl;
			return -1;
		}

		//set input data for the operation
		op->setInputData(array.get());

		//here we have too loop over all rois in the list of rois - if a ROI is given
		//alternatively a single mask image can be given
		//here we need to place a try statement in future to catch exceptions from
		//ROI mismatch!
		if(rois.empty()){
			op->run();
			result = op->getResult();
			std::cout<<((Float128Scalar *)(result))->getValue()<<std::endl;
		}else{
			ROIList::iterator roi;
			for(roi = rois.begin(); roi != rois.end(); roi++){
				try{
					op->applyROI(*roi);
				}
				catch(ROIRankError &e){
					std::cerr<<e<<std::endl;
					return -1;
				}
				catch(ROIRangeError &e){
					std::cerr<<e<<std::endl;
					return -1;
				}

				op->run();
				result = op->getResult();
				std::cout<<((Float128Scalar *)(result))->getValue()<<" ";
			}
			std::cout<<std::endl;
		}

	}

	return 0;

}

