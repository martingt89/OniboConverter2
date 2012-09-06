/*
 * settingsloader.cpp
 *
 *  Created on: 30.8.2012
 *      Author: martint
 */

#include "settingsloader.h"
#include <iostream>
#include "../helper.h"

namespace Xml {

SettingsLoader::SettingsLoader(const Path& settingsFilePath) {
	this->settingsFilePath = settingsFilePath;
	std::list<std::string> ffmpeg;
	ffmpeg.push_back("settings");
	ffmpeg.push_back("ffpath");
	pathToProperty.set(ffmpeg, FFMPEG_PATH_PROPERTY);

	std::list<std::string> destination;
	destination.push_back("settings");
	destination.push_back("destination");
	pathToProperty.set(destination, DESTINATION_PATH_PROPERTY);
}

SettingsLoader::~SettingsLoader() {}

bool SettingsLoader::load(){
	path.clear();
	if(!settingsFilePath.exist()){
		return false;
	}
	try{
		this->parse_file(settingsFilePath.getPath());
	}catch(std::exception& ex){
		std::cout<<"Parsovanie sa dojebalo: "<<ex.what()<<std::endl; //todo log
		return false;
	}
	return true;
}

Path SettingsLoader::getFFConverterPath(){
	return Path(propertyToValue.get(FFMPEG_PATH_PROPERTY));
}
Path SettingsLoader::getDestinationPath(){
	return Path(propertyToValue.get(DESTINATION_PATH_PROPERTY));
}

void SettingsLoader::on_start_element(const Glib::ustring& name, const AttributeList& attributes){
	path.push_back(name);
}
void SettingsLoader::on_end_element(const Glib::ustring& name){
	path.pop_back();
}
void SettingsLoader::on_characters(const Glib::ustring& characters){
	std::string value = clearString(characters);
	if(value.size() > 0){
		bool exist = false;
		SettingsProperty prop = pathToProperty.get(path, exist);
		if(exist){
			propertyToValue.set(prop, value);
		}
	}
}

} /* namespace Xml */
