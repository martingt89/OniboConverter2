/*
 * ffpreset.cpp
 *
 *  Created on: 25.7.2012
 *      Author: martint
 */

#include "ffpreset.h"
#include "../RegexTools/regextools.h"
#include <giomm/file.h>

#include <iostream> //todo remove
namespace ConverterOptions {

FFpreset::FFpreset(const Path& path): ffpresetFolderPath(path){

	try{
		Glib::RefPtr< Gio::File > directory = Gio::File::create_for_path(path.getPath());

		if(!directory){
			std::cerr<<"folder not found"<<std::endl;
			return;
		}
		Glib::RefPtr<Gio::FileEnumerator> enumerator = directory->enumerate_children();
		if(!enumerator){
			std::cerr << "Gio::File::enumerate_children() returned an empty RefPtr." << std::endl;
			return;
		}

		RegexTools::Regex reg("^([^-]+)-.*\\.ffpreset");

		Glib::RefPtr<Gio::FileInfo> file_info = enumerator->next_file();
		while(file_info){
			if(file_info->get_file_type() == Gio::FILE_TYPE_REGULAR ){
				RegexTools::Matcher match = reg.getMatcher(file_info->get_name());
				if(match.find()){
					FFfile file;
					file.path = Glib::build_filename(directory->get_path (), file_info->get_name());
					std::string filePrefix = match.getGroup(1);
					file.name = trimName(file_info->get_name(), filePrefix);
					ffpreset.set(filePrefix, file);
				}
			}
			file_info = enumerator->next_file();
		}
	}catch(const Glib::Exception& ex){
		std::cerr<<ex.what()<<std::endl;
	}
}

FFpreset::~FFpreset(){

}

void FFpreset::addUserDefineFile(const std::string& prefix, const std::string& path){
	FFfile file;
	file.path = path;
	file.name = trimName(path, prefix);
	ffpreset.set(prefix, file);
}

bool FFpreset::getFFpresets(const std::string& prefix,
		std::list<std::pair<std::string, std::string> > &ffpresets){

	if(!ffpreset.isExist(prefix)){
		return false;
	}
	std::list<FFfile> files = ffpreset.get(prefix);
	for(auto fileIter =files.begin(); fileIter != files.end(); ++fileIter){
		ffpresets.push_back(std::make_pair(fileIter->name, fileIter->path));
	}
	return true;
}

std::string FFpreset::trimName(const std::string& name, const std::string& prefix){
	std::string::size_type lastSeparator = name.find_last_of("/");
	std::string fileName = name;
	if(lastSeparator != std::string::npos){
		fileName = name.substr(lastSeparator+1);
	}
	if(fileName.find(prefix+"-") == 0){
		fileName = fileName.substr(prefix.size()+1);
	}
	std::string::size_type sufixPos = fileName.find(".ffpreset");
	if(sufixPos == fileName.size() - std::string(".ffpreset").size()){
		fileName = fileName.substr(0, sufixPos);
	}
	return fileName;
}

} /* namespace ConverterOptions */
