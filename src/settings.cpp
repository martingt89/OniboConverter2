/*
 * settings.cpp
 *
 *  Created on: 20.6.2012
 *      Author: martint
 */

#include "settings.h"
#include "helper.h"

Settings* Settings::settings = 0;

Settings* Settings::getSettings(){
	if(settings == 0){
		settings = new Settings();
	}
	return settings;
}

std::string Settings::getValue(Set name) throw (SettingsNotFoundException){
	std::map<Set, std::string>::iterator it = content.find(name);
	if(it != content.end()){
		return it->second;
	}
	throw SettingsNotFoundException(std::string("Settings not found: ") + toString(name));
	return NULL;
}

void Settings::setValue(Set name, std::string value){
	content[name] = value;
}
