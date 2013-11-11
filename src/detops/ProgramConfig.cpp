
#include<string>
#include<vector>

#include "ProgramConfig.hpp"

ProgramConfig::ProgramConfig() {
	_vmap = new popts::variables_map();
	_odesc = new popts::options_description("Programm options");

	//set command line options
	_odesc->add_options()
			("help,h","print help message")
			("verbose,v","print verbose text during processing")
			("print-files,f","print file name along with output")
			("iformat",popts::value<pni::utils::String>(),"input format")
			("roi,r",popts::value<std::vector<pni::utils::String> >()->composing(),"set region of interest")
			("mask,m",popts::value<std::string>(),"set mask image")
			("background,b",popts::value<std::string>(),"set background image")
			("command,c",popts::value<std::string>(),"set the command")
			("exposure,e",popts::value<double>()->default_value(1),"exposure time")
			("norm,n",popts::value<double>()->default_value(1),"normalization value")
			("input-files",popts::value<ProgramConfig::InputFileList>(),"input files")
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

double ProgramConfig::getNorm() const {
	return (*_vmap)["norm"].as<double>();
}

double ProgramConfig::getExposure() const {
	return (*_vmap)["exposure"].as<double>();
}

int ProgramConfig::help() const {
	if (_vmap->count("help")) {
		std::cout << *_odesc << std::endl;
		return 1;
	}
	return 0;
}

std::string ProgramConfig::getMask() const {
	if (_vmap->count("mask")) {
		return (*_vmap)["mask"].as<std::string> ();
	} else {
		return std::string("none");
	}
}

std::string ProgramConfig::getCommand() const {
	if (_vmap->count("command")) {
		return (*_vmap)["command"].as<std::string> ();
	} else {
		return std::string("sum");
	}
}

std::string ProgramConfig::getBackground() const {
	if (_vmap->count("background")) {
		return (*_vmap)["background"].as<std::string> ();
	} else {
		return std::string("none");
	}
}

std::string ProgramConfig::getInputFormat() const {
	if(_vmap->count("iformat")){
		return (*_vmap)["iformat"].as<std::string>();
	}else{
		return std::string("cbf");
	}
}

void ProgramConfig::setROIList(ROIList &rl) const {
	//clear the ROI list
	rl.clear();

	//start with option evaluation
	if(_vmap->count("roi")){
		std::vector<pni::utils::String> ov= (*_vmap)["roi"].as<std::vector<pni::utils::String> >();
		std::vector<pni::utils::String>::iterator roi_iter;

		roi_separator range_sep(",");  //ranges are separated by a comma
		roi_separator chann_sep(":");  //channel seperator
		roi_token_iterator range_iter; //iterator over ranges in a roi string
		roi_token_iterator chann_iter; //iterator over each channel

		//now we iterate over all ROIs specified by the user
		//each -r entry on the command lines specifies a new ROI
		for(roi_iter = ov.begin();roi_iter!=ov.end();roi_iter++){
			pni::utils::String rstr = *roi_iter;

			ROI roi;
			roi_tokenizer range_tokens(rstr,range_sep);

			//iterate over all ranges in the roi string
			for(range_iter = range_tokens.begin(); range_iter != range_tokens.end(); range_iter++){
				//std::cout<<*range_iter<<std::endl;
				pni::utils::String cstr = *range_iter;
				//now we have to create a ROIRange from each of the strings

				//check if only one number is given - only a single channel along this
				//dimension should be taken
				pni::utils::UInt64 start_ch=0, stop_ch=0;
				if(cstr.find(":")){
					//if different start and stop channels are used
					roi_tokenizer chann_tokens(cstr,chann_sep);
					pni::utils::UInt64 cnt=0;
					for(chann_iter = chann_tokens.begin(); chann_iter != chann_tokens.end(); chann_iter++,cnt++){
						pni::utils::String s = *chann_iter;
						if(cnt==0) start_ch = (pni::utils::UInt64)std::atoi(s.c_str());
						if(cnt==1) stop_ch = (pni::utils::UInt64)std::atoi(s.c_str());
					}
				}else{
					//if only one channel is selected
					start_ch = (pni::utils::UInt64)std::atoi(cstr.c_str());
					stop_ch  = start_ch;
				}
				roi.appendRange(ROIRange(start_ch,stop_ch));
			}

			rl.push_back(roi);

		}

		//parse here for ROI data
		//roi_separator sep(",");
		//roi_tokenizer tokens((*_vmap)["roi"].as<std::string>(),sep);
		//roi_token_iterator iter;
		//unsigned long cnt;
		//ROI2D *roi = new ROI2D();

		//for(iter=tokens.begin(),cnt=0;iter!=tokens.end();++iter,++cnt){
			//if(cnt==0) roi->getROIX()->set(*iter);
			//if(cnt==1) roi->getROIY()->set(*iter);
		//}


	}
}

ProgramConfig::InputFileList *ProgramConfig::getInputFileList() const{
	ProgramConfig::InputFileList *l = new ProgramConfig::InputFileList;
	if(_vmap->count("input-files")){
		*l = (*_vmap)["input-files"].as<ProgramConfig::InputFileList>();
		return l;
	}else{
		return NULL;
	}
}

bool ProgramConfig::isVerbose() const {
	if (_vmap->count("verbose")){
		return true;
	}else{
		return false;
	}
}

bool ProgramConfig::printFileNames() const {
	if(_vmap->count("print-files")){
		return true;
	}else{
		return false;
	}
}
