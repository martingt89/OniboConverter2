/*
 * settingsgenerator.cpp
 *
 *  Created on: 30.8.2012
 *      Author: martint
 */

#include "settingsgenerator.h"
#include <fstream>
namespace Xml {

SettingsGenerator::SettingsGenerator(const Path& settingsFile, const Path& ffmpegPath,
		const Path& destination) : settingsFile(settingsFile),
		ffmpegPath(ffmpegPath), destination(destination){
}

SettingsGenerator::~SettingsGenerator() {
	// TODO Auto-generated destructor stub
}

void SettingsGenerator::setFFpath(const Path& ffmpegPath){
	this->ffmpegPath = ffmpegPath;
}
void SettingsGenerator::setDestination(const Path& destination){
	this->destination = destination;
}
void SettingsGenerator::save(){
	XmlGenerator generator;
	XmlDocument* settings = generator.createDocument("settings");
	settings->addSubNode(generator.createNode("ffpath"))->addText(ffmpegPath.getPath());
	settings->addSubNode(generator.createNode("destination"))->addText(destination.getPath());
	std::stringstream ss;
	settings->write(ss);
	std::ofstream file(settingsFile.getPath());
	file << ss.str();
	file.close();
	delete settings;
}
} /* namespace Xml */
