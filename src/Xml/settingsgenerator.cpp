/*
 * settingsgenerator.cpp
 *
 *  Created on: 30.8.2012
 *      Author: martint
 */

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
	doc->write(file);
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
