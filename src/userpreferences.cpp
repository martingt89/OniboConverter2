/*
 * userpreferences.cpp
 *
 *  Created on: 6.9.2012
 *      Author: martin
 */

#include "userpreferences.h"
#include "helper.h"
#include "globalsettings.h"
#include "Xml/settingsloader.h"
#include <glibmm/miscutils.h>

static const std::string EXTERNAL_CONVERTER = "ffmpeg";

UserPreferences* UserPreferences::instance = 0;

UserPreferences* UserPreferences::getInstance(){
	if(instance == 0){
		instance = new UserPreferences();
	}
	return instance;
}

UserPreferences::UserPreferences() {
	setConvertDestinationPath(Path(Glib::get_home_dir()));
	setExtConverterPath(Path(EXTERNAL_CONVERTER));
	setNumberOfCPU(-1, true);
	setMultithreadingForEncoders(true);
	//
	Xml::SettingsLoader loader(GlobalSettings::getInstance()->getUserSettingsFile());
	loader.load(optToValue);
}

UserPreferences::~UserPreferences() {}

void UserPreferences::setConvertDestinationPath(const Path& destination){
	optToValue.set(UserPreferences::DESTINATION_PATH, destination.getPath());
}
void UserPreferences::setExtConverterPath(const Path& path){
	optToValue.set(UserPreferences::EXT_CONVERTER_PATH, path.getPath());
}
void UserPreferences::setNumberOfCPU(const int& number, bool automatic){
	if(automatic){
		optToValue.set(UserPreferences::NUM_OF_CPU, toS(-1));
	}else{
		optToValue.set(UserPreferences::NUM_OF_CPU, toS(number));
	}
}
void UserPreferences::setMultithreadingForEncoders(const bool& support){
	int value = 0;
	if(support){
		value = 1;
	}
	optToValue.set(UserPreferences::ENABLE_MULTITHREAD_FOR_ENC, toS(value));
}
//
Path UserPreferences::getConvertDestinationPath() const{
	bool exist = false;
	std::string value = optToValue.get(UserPreferences::DESTINATION_PATH, exist);
	assert(exist, "Options: UserPreferences::DESTINATION_PATH doesn't exist");
	return Path(value);
}
Path UserPreferences::getExtConverterPath() const{
	bool exist = false;
	std::string value = optToValue.get(UserPreferences::EXT_CONVERTER_PATH, exist);
	assert(exist, "Options: UserPreferences::EXT_CONVERTER_PATH doesn't exist");
	return Path(value);
}
int UserPreferences::getNumerOfCPU() const{
	bool exist = false;
	std::string value = optToValue.get(UserPreferences::NUM_OF_CPU, exist);
	assert(exist, "Options: UserPreferences::NUM_OF_CPU doesn't exist");
	return toN(value, int());
}
bool UserPreferences::isAutomaticNumberOfCPU() const{
	bool exist = false;
	std::string value = optToValue.get(UserPreferences::NUM_OF_CPU, exist);
	assert(exist, "Options: UserPreferences::NUM_OF_CPU doesn't exist");
	return (toN(value, int()) == -1);
}
bool UserPreferences::isMultithreadinForEncoders() const{
	bool exist = false;
	std::string value = optToValue.get(UserPreferences::ENABLE_MULTITHREAD_FOR_ENC, exist);
	assert(exist, "Options: UserPreferences::ENABLE_MULTITHREAD_FOR_ENC doesn't exist");
	return toN(value, int()) == 1;
}
//
void UserPreferences::save(){
	Xml::SettingsGenerator generator(GlobalSettings::getInstance()->getUserSettingsFile());
	generator.save(optToValue);
}
