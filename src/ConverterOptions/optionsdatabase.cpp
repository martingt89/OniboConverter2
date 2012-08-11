/*
 * optionsdatabase.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "optionsdatabase.h"

namespace ConverterOptions {

OptionsDatabase::OptionsDatabase(OptionsLoader* optionsLoader) {
	framerates = optionsLoader->loadFramerates();
	samplerates = optionsLoader->loadSamplerates();
	containers = optionsLoader->loadContainers();
	resolutions = optionsLoader->loadResolutions();
	channels = optionsLoader->loadChannels();
}

OptionsDatabase::~OptionsDatabase() {}

const OptionsDatabase& OptionsDatabase::operator=(const OptionsDatabase& database){
	return database;
}

OptionsDatabase::OptionsDatabase(const OptionsDatabase&){}

const Framerates& OptionsDatabase::getFramerates() const{
	return framerates;
}
const Samplerates& OptionsDatabase::getSamplerates() const{
	return samplerates;
}
const Containers& OptionsDatabase::getContainers() const{
	return containers;
}
const Resolutions& OptionsDatabase::getResolutions() const{
	return resolutions;
}
const Channels& OptionsDatabase::getChannels() const{
	return channels;
}
void OptionsDatabase::addUserResolution(const Resolution& resolution){
	userResolutions.push_back(resolution);
}
void OptionsDatabase::addUserVideoBitrate(const Bitrate& bitrate){
	userVideoBitrate.push_back(bitrate);
}
void OptionsDatabase::addUserAudioBitrate(const Bitrate& bitrate){
	userAudioBitrate.push_back(bitrate);
}
//
std::list<Resolution> OptionsDatabase::getUserResolutions() const{
	return userResolutions;
}
std::list<Bitrate> OptionsDatabase::getUserVideoBitrate() const{
	return userVideoBitrate;
}
std::list<Bitrate> OptionsDatabase::getUserAudioBitrate() const{
	return userAudioBitrate;
}

} /* namespace ConverterOptions */
