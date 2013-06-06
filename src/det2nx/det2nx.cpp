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


#include "det2nx.hpp"
#include "../common/config_utils.hpp"
#include "../common/file_list_parser.hpp"

static const string program_name = "det2nx";
static const string help_header = "det2nx takes the following command line options";

static const string_list cbf_exts = {".cbf",".CBF"};
static const string_list tif_exts = {".tif",".TIF",".tiff",".TIFF"};

int main(int argc,char **argv)
{
    //create configuration
    configuration config = create_configuration();
  
    //parse command line options and arguments
    if(parse_cli_opts(argc,argv,program_name,config)) return 1;

    //check if the user requested help 
    if(check_help_request(config,help_header)) return 1;

    //-------------------------generating the input file list------------------
    try
    {
        //------------------dealing with input data----------------------------
        //create the input file list - this will throw a file_error exception if
        //one of the input files does not exist
        auto infiles = file_list_parser::parse<file_list>(
                config.value<string_vector>("input-files"));
        std::cout<<"processing "<<infiles.size()<<" files ..."<<std::endl;

        //the first image in the stack determines the file type and all other
        //image paramters (like data type and shape)

        //at first we need to obtain the appropriate reader
        reader_ptr reader = get_reader(infiles,cbf_exts,tif_exts);

        //get thre reference image information object
        pni::io::image_info info = get_image_info(reader,infiles.begin()->path());

        //need to check all the input files
        check_input_files(infiles,reader,info);

        //--------------parse the nexus path to get target information----------
        nxpath nexus_path = path_from_string(config.value<string>("target"));
        
        //need to check the validity of the path
        if(nexus_path.filename().empty())
            throw file_error(EXCEPTION_RECORD,"No output file given!");

        if(!nexus_path.attribute().empty())
            throw file_error(EXCEPTION_RECORD,
                    "Nexus target must not be an attribute!");

        //------------------------opening the output file-----------------------
        //have to create the file name of the output file
        h5::nxfile output_file = open_output_file(nexus_path.filename());

        //----------------check for target objects------------------------------
        //create the array object where to store the input data
        shape_t frame_shape{info.nx(),info.ny()};

    }
    catch(file_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(cli_option_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }


    //-------------------processing input files--------------------------------


    /*
	//create the shape objects for the data
	shape_t sframe(array->getShape());  //shape of a single detector frame
	shape_t sdata;   //shape of the full data block
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
    nxfield = nconfig.value<string>("nx-path");
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
    */
	return 0;
}

