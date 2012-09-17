/* ---------------------------------------------------------------------------
** Author: Martin Geier
** settingsloader.cpp is part of OniboConverter2.
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
