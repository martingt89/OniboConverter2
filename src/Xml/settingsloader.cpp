/*
 * settingsloader.cpp
 *
 *  Created on: 30.8.2012
 *      Author: martint
 */

#include "settingsloader.h"
#include "xmlparser.h"
#include "../helper.h"
#include "../xmlfilesdefinitions.h"

namespace Xml {

SettingsLoader::SettingsLoader(const Path& settingsFilePath) {
	this->settingsFilePath = settingsFilePath;
}

SettingsLoader::~SettingsLoader() {}

bool SettingsLoader::load(CppExtension::HashMap<UserPreferences::UserPreferencesOpt, std::string>& optToValue){
	XmlParser parser;
	XmlParserData data;
	if(!parser.parseFile(settingsFilePath, &data)){
		return false;
	}
	auto& definition = XmlFilesDefinitions::getInstance()->getUserPreferencesTable();
	for(auto record : data){
		UserPreferences::UserPreferencesOpt option;
		if(definition.getOptionsFromList(record.first, option)){
			optToValue.set(option, record.second);
		}
	}
	return true;
}

} /* namespace Xml */
