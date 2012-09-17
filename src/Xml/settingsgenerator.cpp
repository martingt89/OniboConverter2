/* ---------------------------------------------------------------------------
** Author: Martin Geier
** settingsgenerator.cpp is part of OniboConverter2.
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

#include "settingsgenerator.h"
#include "../xmlfilesdefinitions.h"
#include <fstream>

namespace Xml {

SettingsGenerator::SettingsGenerator(const Path& settingsFile) : settingsFile(settingsFile){}

SettingsGenerator::~SettingsGenerator() {}

void SettingsGenerator::save(CppExtension::HashMap<UserPreferences::UserPreferencesOpt, std::string> optToValue){
	auto& table = XmlFilesDefinitions::getInstance()->getUserPreferencesTable();
	XmlGenerator generator("settings");
	for(int opt = UserPreferences::BEGIN; opt != UserPreferences::END; ++opt){
		UserPreferences::UserPreferencesOpt options = (UserPreferences::UserPreferencesOpt)opt;
		auto list = table.getListFromOptions(options);
		std::string value = optToValue.get(options);
		std::vector<PathNode> path = toPathVector(list, value);
		generator.addPath(path);
	}
	std::unique_ptr<Document> doc = generator.generateFromPath();
	std::ofstream file(settingsFile.getPath());
	(*doc).write(file);
	file.close();
}
std::vector<PathNode> SettingsGenerator::toPathVector(std::list<std::string> list, std::string value){
	std::vector<PathNode> pathVector;
	if(list.size() > 0){
		auto last = list.end();
		--last;
		for(auto iter = list.begin(); iter != last; ++iter){
			pathVector.push_back(PathNode(*iter));
		}
		pathVector.push_back(PathNode(*last, value));
	}
	return pathVector;
}
} /* namespace Xml */
