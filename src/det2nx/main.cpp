/*
 * main.cpp
 *
 * Main program for det2nx - a tool for converting arbitrary detector
 * data in valid Nexus files.
 *
 *  Created on: Jun 30, 2011
 *      Author: Eugen Wintersberger
 */


#include <iostream>
#include <pni/utils/PNITypes.hpp>
//#include <pni/utils/ScalarObject.hpp>
#include <pni/utils/Scalar.hpp>
#include <pni/nx/NX.hpp>
#include <boost/filesystem.hpp>

#include "Det2NxConfig.hpp"
#include "../common/DetectorReader.hpp"

using namespace pni::nx::h5;
using namespace pni::utils;
namespace fs = boost::filesystem;


int main(int argc,char **argv){
	Det2NxConfig conf;
	Det2NxConfig::InputFileList *iflist;

	//if too less arguments are passed to the program exit
	if(argc<2){
		std::cerr<<"Usage: det2nx [options] FILE ..."<<std::endl;
		std::cerr<<"Use det2nx -h for more information!"<<std::endl;
		return 1;
	}

	//parse the command line options
	conf.parse(argc,argv);

	//print help and exit
	if(conf.help()) return 0;

	//get the list of input files
	iflist = conf.getInputFileList();

	//have to create the file name of the output file
	fs::path ofile(conf.getOutputFile());
	NXFile nxofile;
	nxofile.setFileName(ofile.string());
	if((!fs::exists(ofile))||conf.getOverwrite()){
		//if the file does not already exist we need to create it
		nxofile.setOverwrite(true);
		nxofile.setSplitSize(conf.getSplitSize());
		nxofile.create();
	}else{
		//the file exists
		nxofile.setReadOnly(false);
		nxofile.open();
	}

	//we need to read the first file to obtain all information needed
	//to store the data
	DetectorReader reader;
	reader.setInputFile((*iflist)[0]); reader();
	ArrayObject::sptr array = reader.getData();

	//create the shape objects for the data
	Shape sframe(array->getShape());  //shape of a single detector frame
	Shape sdata;   //shape of the full data block
	sdata.setRank(sframe.getRank()+1);
	sdata.setDimension(0,iflist->size());
	for(UInt32 i=0;i<sframe.getRank();i++) sdata.setDimension(i+1,sframe.getDimension(i));

	//setup the selection for partial data IO
	NXSelection sel;
	sel.setDiskRank(sdata.getRank());
	sel.setCount(0,1);
	for(UInt32 i=0;i<sframe.getRank();i++) sel.setCount(i+1,sframe.getDimension(i));
	//set offset values
	for(UInt32 i=0;i<sel.getDiskRank();i++) sel.setOffset(i,0);

	NXGroup g;
	String field_path = "/"+conf.getEntryName()+"/"+conf.getInstrumentName()+"/"+conf.getDetectorName();
	if(!nxofile.exists(field_path)){
		g = nxofile.createGroup(field_path);
	}else{
		g = nxofile.openGroup(field_path);
	}

	//creat the field where to store the data
	NXField field;
	if(g.exists("data")){
		//if data already exists we have to check some options
		if(conf.getReplace()){
			g.remove("data");
			if(conf.getCompression()=="deflate"){
				NXDeflateFilter filter;
				field = g.createField("data",array->getTypeID(),sdata,filter);
			}else if(conf.getCompression()=="lzf"){
				NXLZFFilter filter;
				field = g.createField("data",array->getTypeID(),sdata,filter);
			}else{
				field = g.createField("data",array->getTypeID(),sdata);
			}
		}else if(conf.getAppend()){
			field = g.openField("data");
			//set the offset to the new starting point
			sel.setOffset(0,field.getShape().getDimension(0));
			field.resize(field.getShape().getDimension(0)+sdata.getDimension(0));

		}else{
			//abort the program here
			g.close();
			nxofile.close();
			std::cerr<<"Data field already exists!"<<std::endl;
			return 1;
		}
	}else{
		if(conf.getCompression()=="deflate"){
			NXDeflateFilter filter;
			field = g.createField("data",array->getTypeID(),sdata,filter);
		}else if(conf.getCompression()=="lzf"){
			NXLZFFilter filter;
			field = g.createField("data",array->getTypeID(),sdata,filter);
		}else{
			field = g.createField("data",array->getTypeID(),sdata);
		}
	}

	//register selection with the field
	field.registerSelection(sel);

	//loop over all files and write the data
	Det2NxConfig::InputFileIterator iter;
	for(iter = iflist->begin();iter != iflist->end();++iter){
		if(conf.isVerbose()){
			std::cout<<"processing file: "<<*iter<<" ..."<<std::endl;
		}
		reader.setInputFile(*iter);
		reader();
		array = reader.getData();
		field.write(*array);
		//nxofile.flush();
		sel.incOffset(0);
	}




	//loop over all files
	g.close();
	field.close();
	nxofile.close();
	return 0;
}

