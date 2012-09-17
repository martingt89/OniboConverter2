/* ---------------------------------------------------------------------------
** Author: Martin Geier
** userpreferences.cpp is part of OniboConverter2.
**
** OniboConverter2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
** -------------------------------------------------------------------------*/
#include <glibmm/miscutils.h>
#include "userpreferences.h"
#include "helper.h"
#include "systemsettings.h"
#include "Xml/settingsloader.h"

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
	setDisableShowUnEncoders(false);
	//
	Xml::SettingsLoader loader(SystemSettings::getInstance()->getUserSettingsFile());
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
void UserPreferences::setDisableShowUnEncoders(const bool& disable){
	optToValue.set(UserPreferences::DISABLE_SHOW_UNENCODER, toS(disable));
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
bool UserPreferences::isDisableShowUnEncoders() const{
	bool exist = false;
	std::string value = optToValue.get(UserPreferences::DISABLE_SHOW_UNENCODER, exist);
	assert(exist, "Options: UserPreferences::DISABLE_SHOW_UNENCODER doesn't exist");
	return (bool)toN(value, int());
}
//
void UserPreferences::save(){
	Xml::SettingsGenerator generator(SystemSettings::getInstance()->getUserSettingsFile());
	generator.save(optToValue);
}
