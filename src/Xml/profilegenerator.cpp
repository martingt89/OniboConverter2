/* ---------------------------------------------------------------------------
** Author: Martin Geier
** profilegenerator.cpp is part of OniboConverter2.
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

#include <fstream>
#include "profilegenerator.h"
#include "../xmlfilesdefinitions.h"
#include "../helper.h"
#include <iostream> //todo remove
namespace Xml {

static void getManualXml(const std::list<Profile::Profile::ManualSettings> manualSettings,
		Xml::Node* doc) {

	Xml::Node* manualNod = doc->addSubNode(new Node("manualsettings"));

	for(auto manual : manualSettings){
		Xml::Node* settingNod = manualNod->addSubNode(new Node("setting"));
		settingNod->addSubNode(new Node("command"))->setText(manual.command);
		for(auto arg : manual.args){
			settingNod->addSubNode(new Node("arg"))->setText(arg);
		}
	}
}

ProfileGenerator::ProfileGenerator(const Path& outputDirectory) : outputDirectory(outputDirectory){}

ProfileGenerator::~ProfileGenerator() {}

void ProfileGenerator::generateFile(const Profile::Configuration& profileConfiguration, std::string profileFileName){
	auto& table = XmlFilesDefinitions::getInstance()->getConfigurationTable();
	XmlGenerator generator("profile");
	for(int opt = Profile::Configuration::BEGIN_OPT;
			opt != Profile::Configuration::END_OPT; ++opt){
		Profile::Configuration::Options options = (Profile::Configuration::Options)opt;
		auto list = table.getListFromOptions(options);
		std::string value = profileConfiguration.getProperty(options);
		std::vector<PathNode> path = toPathVector(list, value);
		generator.addPath(path);
	}

	std::unique_ptr<Document> doc = generator.generateFromPath();

	std::list<Profile::Profile::ManualSettings> manualSettings;
	profileConfiguration.getManualSettings(manualSettings);

	getManualXml(manualSettings, (*doc).getNode());

	if(profileFileName == std::string()){
		profileFileName = getActualTimeMiliSec();
	}

	std::string xmlFileName = profileFileName + ".xml";
	Path outputPath(outputDirectory.getPath(), xmlFileName);
	std::cout<<"output: "<<outputPath.getPath()<<std::endl;
	std::ofstream file(outputPath.getPath());
	if(!file){
		std::cerr<<"Cannot create file"<<std::endl;
	}else{
		(*doc).write(file);
		file.close();
	}
}

std::vector<PathNode> ProfileGenerator::toPathVector(std::list<std::string> list, std::string value){
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
