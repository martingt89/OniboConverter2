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

FFpreset::FFpreset(){
	name = "";
	buildin = false;
}
FFpreset::FFpreset(const Path& path, const std::string& prefix, const bool& buildin){
	ffpresetFilePath = path;
	name = cropName(path.getPath(), prefix);
	this->prefix = prefix;
	this->buildin = buildin;
}
FFpreset::~FFpreset(){

}
std::string FFpreset::toStr() const{
	return name;
}
std::string FFpreset::getPrefix() const{
	return prefix;
}
Path FFpreset::getPath() const{
	return ffpresetFilePath;
}
std::string FFpreset::getName() const{
	return ffpresetFilePath.getLastPathPart();
}
bool FFpreset::isBuildIn() const{
	return buildin;
}
Converter::ConvertSettingsList  FFpreset::getConvertArguments() const{
	Converter::ConvertSettingsList args;
	Converter::ConvertSettings arg(Converter::ConvertSettings::FFPRESET);
	arg.addValue(ffpresetFilePath.getPath());
	args.add(arg);
	return args;
}
//
std::string FFpreset::cropName(const std::string& name, const std::string& prefix){
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
//
FFpresets::FFpresets(){
	prefix = "";
}
FFpresets::FFpresets(const std::string& prefix){
	this->prefix = prefix;
}
FFpresets::FFpresets(const std::string& prefix, const Path& ffpresetsDirectory, const bool& buildin){
	this->prefix = prefix;
	loadFromFolder(ffpresetsDirectory, buildin);
}
void FFpresets::addFFpreset(const FFpreset& ffpreset){
	ffpresets.push_back(ffpreset);
}

bool FFpresets::loadFromFolder(const Path& path, const bool& buildin){
	try{
		Glib::RefPtr< Gio::File > directory = Gio::File::create_for_path(path.getPath());

		if(!directory){
			std::cerr<<"folder not found"<<std::endl;
			return false;
		}
		Glib::RefPtr<Gio::FileEnumerator> enumerator = directory->enumerate_children();
		if(!enumerator){
			std::cerr << "Gio::File::enumerate_children() returned an empty RefPtr." << std::endl;
			return false;
		}

		RegexTools::Regex ffpresetPatern("^([^-]+)-.*\\.ffpreset");

		Glib::RefPtr<Gio::FileInfo> file_info = enumerator->next_file();
		while(file_info){
			if(file_info->get_file_type() == Gio::FILE_TYPE_REGULAR ){
				RegexTools::Matcher match = ffpresetPatern.getMatcher(file_info->get_name());
				if(match.find()){
					Path FFfile(Glib::build_filename(directory->get_path (), file_info->get_name()));
					std::string filePrefix = match.getGroup(1);
					if(filePrefix == prefix){
						FFpreset ff(FFfile, filePrefix, buildin);
						this->addFFpreset(ff);
					}
				}
			}
			file_info = enumerator->next_file();
		}
	}catch(const Glib::Exception& ex){
		std::cerr<<ex.what()<<std::endl;
		return false;
	}
	return true;
}
std::list<FFpreset> FFpresets::getFFpresetList(){
	return ffpresets;
}

} /* namespace ConverterOptions */
