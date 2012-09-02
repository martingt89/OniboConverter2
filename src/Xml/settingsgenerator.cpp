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

SettingsGenerator::~SettingsGenerator() {}

void SettingsGenerator::setFFpath(const Path& ffmpegPath){
	this->ffmpegPath = ffmpegPath;
}
void SettingsGenerator::setDestination(const Path& destination){
	this->destination = destination;
}
void SettingsGenerator::save(){					//todo to automat version
	Xml::Document* settings = new Document();
	Xml::Node* node = settings->setSubNode(new Xml::Node("settings"));
	node->addSubNode(new Xml::Node("ffpath"))->setText(ffmpegPath.getPath());
	node->addSubNode(new Xml::Node("destination"))->setText(destination.getPath());
	std::ofstream file(settingsFile.getPath());
	settings->write(file);
	file.close();
	delete settings;
}
} /* namespace Xml */
