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
 * Created on: 30.06.2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <iostream>
#include <pni/core/types.hpp>
#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>
#include <pni/io/nx/nx.hpp>
#include "../common/file.hpp"
#include "../common/file_list.hpp"
#include "../common/exceptions.hpp"
#include <boost/filesystem.hpp> 

using namespace pni::io::nx::h5;
using namespace pni::core;
namespace fs = boost::filesystem;

typedef std::vector<string> strlist;

int main(int argc,char **argv)
{
    configuration config;

    config.add_option(config_option<bool>("help","h",
                "show short help text",false));
    config.add_option(config_option<string>("output","o",
                "output file","output.h5.nx"));
    config.add_option(config_option<string>("nx-path","p",
                "target path","/entry/instrument/detector"));
    config.add_option(config_option<string>("field","f",
                "target field","data"));
    config.add_option(config_option<bool>("append","a",
                "append data to existing field",true));
    config.add_argument(config_argument<strlist>("input-files",-1,strlist{"-"}));
    
    try
    {
        parse(config,cliargs2vector(argc,argv));
    }
    catch(...)
    {
        std::cerr<<"Wrong or insufficient command line options:"<<std::endl;
        std::cerr<<std::endl;
        std::cerr<<"use det2nx -h for more info"<<std::endl;
        return 1;
    }

    //check for help request by the user
    if(config.value<bool>("help"))
    {
        std::cerr<<"det2nx takes the following command line options";
        std::cerr<<std::endl<<std::endl;
        std::cerr<<config<<std::endl;
        return 1;
    }
   
    //-------------------------generating the input file list------------------
    file_list infiles;
    try
    {
        auto path_list = config.value<strlist>("input-files");
        infiles = file_list(path_list);
    }
    catch(file_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }

    //------------------------opening the output file--------------------------
	//have to create the file name of the output file
	fs::path output_file_path(config.value<string>("output"));
	nxfile output_file;

	if((!fs::exists(output_file_path)))
    {
		//if the file does not already exist we need to create it
        output_file = nxfile::create_file(config.value<string>("output"));
	}
    else
    {
        //open an existing output file
        output_file = nxfile::open_file(config.value<string>("output"));
	}
    
    //-------------------processing input files--------------------------------
    for(auto file: infiles)
    {
        pni::io::image_info info;
        if(file.extension()==".cbf")
        {
            pni::io::cbf_reader reader(file.path());
            info = reader.info(0);
        }
        else if(file.extension()==".tiff")
        {
            pni::io::tiff_reader reader(file.path());
            info = reader.info(0);
        }
        else
        {
            throw file_type_error(EXCEPTION_RECORD,"File ["+file.path()+"] is of"
                    "unknown type!");
        }

        if(config.value<bool>("full-path"))
            std::cout<<file.path();
        else
            std::cout<<file.name();

        std::cout<<" ("<<info.nx()<<" x "<<info.ny()<<") ntot = "<<info.npixels();
        std::cout<<" type = "<<info.get_channel(0).type_id()<<std::endl;

    }




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

