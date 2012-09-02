/*
 * profilegenerator.cpp
 *
 *  Created on: 2.9.2012
 *      Author: martint
 */

#include <fstream>
#include "profilegenerator.h"
#include "xmlprofiletable.h"
#include "../helper.h"

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

void ProfileGenerator::generateFile(const Profile::Profile& profile){
	XmlProfileTable table;
	XmlGenerator generator("profile");
	for(int opt = Profile::Profile::BEGIN_OPT;
			opt != Profile::Profile::END_OPT; ++opt){
		Profile::Profile::Options options = (Profile::Profile::Options)opt;
		auto list = table.getListFromOptions(options);
		std::string value = profile.getProperty(options);
		std::vector<PathNode> path = toPathVector(list, value);
		generator.addPath(path);
	}

	std::unique_ptr<Document> doc = generator.generateFromPath();

	std::list<Profile::Profile::ManualSettings> manualSettings;
	profile.getManualSettings(manualSettings);

	getManualXml(manualSettings, doc->getNode());

	std::string xmlFileName = getActualTimeMiliSec()+".xml";

	std::ofstream file(outputDirectory.getPath() +"/"+xmlFileName);	//todo implement path joining
	doc->write(file);
	file.close();
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
