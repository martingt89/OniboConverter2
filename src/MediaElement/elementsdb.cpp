/*
 * elementsdb.cpp
 *
 *  Created on: 9.9.2012
 *      Author: martin
 */

#include "elementsdb.h"

#include "../Xml/optionsloaderxml.h"

namespace MediaElement {

void ElementsDB::load(const Path& configFile, const Path& ffpresetFolder,
		const ConverterOptions::SupportedEncoders& supportedEncoders){
	Xml::OptionsLoaderXml optionsLoaderFromXml(configFile, supportedEncoders, ffpresetFolder);
	containers = optionsLoaderFromXml.loadContainers(elementsRelations);
	formats = optionsLoaderFromXml.loadFormats(elementsRelations);
	audioEncoders = optionsLoaderFromXml.loadAudioEncoders(elementsRelations);
	videoEncoders = optionsLoaderFromXml.loadVideoEncoders(elementsRelations);
	//
	nameToBitrates = optionsLoaderFromXml.loadBitrates();
	nameToAudioGrade = optionsLoaderFromXml.loadAudioGrade();
	channels = optionsLoaderFromXml.loadChannels();
	samplerates = optionsLoaderFromXml.loadSamplerates();
	framerates = optionsLoaderFromXml.loadFramerates();
	resolutions = optionsLoaderFromXml.loadResolutions();
	ffpresets.loadFromFolder(ffpresetFolder, true);
}

Containers ElementsDB::getContainers() const{
	return containers;
}

Formats ElementsDB::getFormats() const{
	return formats;
}

Encoders ElementsDB::getVideoEncoders() const{
	return videoEncoders;
}

Encoders ElementsDB::getAudioEncoders() const{
	return audioEncoders;
}

bool ElementsDB::getBitratesByName(const std::string& name, Bitrates& bitrates) const{
	bool exist;
	bitrates = nameToBitrates.get(name, exist);
	for(auto bit : userBitrates){
		bitrates.push_back(bit);
	}
	return exist;
}
bool ElementsDB::getAudioGradesByName(const std::string& name, AudioGrades& audioGrades) const{
	bool exist;
	audioGrades = nameToAudioGrade.get(name, exist);
	return exist;
}
void ElementsDB::getFFpresetsByPrefix(const std::string& prefix, std::list<FFpreset>& ffpresets) const{
	ffpresets = this->ffpresets.getFFpresetList(prefix);
	auto list = prefixToFFpresets.get(prefix);
	for(auto item : list){
		ffpresets.push_back(item);
	}
}
Framerates ElementsDB::getFramerates() const{
	return framerates;
}
Channels ElementsDB::getChannels() const{
	return channels;
}
Resolutions ElementsDB::getResolutions() const{
	Resolutions resol = resolutions;
	for(auto resolution : userResolutions){
		resolution.setBasic();
		resol.addResolution(resolution);
	}
	return resol;
}
Samplerates ElementsDB::getSamplerates() const{
	return samplerates;
}

void ElementsDB::addUserVideoBitrate(const Bitrate& bitrate){
	for(auto bit : userBitrates){
		if(bit == bitrate){
			return;
		}
	}
	userBitrates.push_back(bitrate);
}
void ElementsDB::addUserResolution(const Resolution& resolution){
	for(auto res : userResolutions){
		if(res == resolution){
			return;
		}
	}
	userResolutions.push_back(resolution);
}
void ElementsDB::addUserFFpreset(const std::string& prefix, const FFpreset& ffpreset){
	prefixToFFpresets.set(prefix, ffpreset);
}

} /* namespace MediaElement */
