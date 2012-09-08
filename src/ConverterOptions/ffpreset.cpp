/*
 * ffpreset.cpp
 *
 *  Created on: 25.7.2012
 *      Author: martint
 */

#include <giomm/file.h>
#include <glibmm/miscutils.h>
#include "ffpreset.h"
#include "../RegexTools/regextools.h"

namespace ConverterOptions {

static const std::string DISABLE_NAME="--- disable ---";

FFpreset::FFpreset(){
	name = "";
	type = DISABLE_FFTYPE;
}

FFpreset::FFpreset(const Path& path, const std::string& prefix, const FFType& type){
	if(type == DISABLE_FFTYPE){
		name = DISABLE_NAME;
	}else{
		name = cropName(path.getPath(), prefix);
	}
	ffpresetFilePath = path;
	this->prefix = prefix;
	this->type = type;
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
FFpreset::FFType FFpreset::getType() const{
	return type;
}
Converter::ConvertSettingsList  FFpreset::getConvertArguments() const{
	Converter::ConvertSettingsList args;
	if(type == DISABLE_FFTYPE){
		return args;
	}
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
//===============================================================================================================
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

void FFpresets::loadFromFolder(const Path& path, const bool& buildin){
	FFpreset::FFType type = FFpreset::USERDEFINED_FFTYPE;
	if(buildin){
		type = FFpreset::BUILDIN_FFTYPE;
	}
	RegexTools::Regex ffpresetPatern("^([^-]+)-.*\\.ffpreset");
	std::list<Path> files;
	if(path.getSubfiles(files)){
		for(auto file : files){
			RegexTools::Matcher match = ffpresetPatern.getMatcher(file.getPath());
			if(match.find()){
				std::string filePrefix = match.getGroup(1);
				if(filePrefix == prefix){
					FFpreset ff(file, filePrefix, type);
					this->addFFpreset(ff);
				}
			}
		}
	}
}
std::list<FFpreset> FFpresets::getFFpresetList(){
	FFpreset disable(std::string(), std::string(), FFpreset::DISABLE_FFTYPE);
	std::list<FFpreset> ff(ffpresets.begin(), ffpresets.end());
	ff.push_front(disable);
	return ff;
}

} /* namespace ConverterOptions */
