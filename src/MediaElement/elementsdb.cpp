/* ---------------------------------------------------------------------------
** Author: Martin Geier
** elementsdb.cpp is part of OniboConverter2.
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

#include "elementsdb.h"

#include "../Xml/optionsloaderxml.h"

namespace MediaElement {

void ElementsDB::load(const Path& configFile, const Path& ffpresetFolder,
		const ConverterOptions::SupportedEncoders& supportedEncoders){
	Xml::OptionsLoaderXml optionsLoaderFromXml(configFile, supportedEncoders, ffpresetFolder);
	containers = optionsLoaderFromXml.loadContainers(elementsRelations);
	formats = optionsLoaderFromXml.loadFormats(elementsRelations);
	audioEncoders = optionsLoaderFromXml.loadAudioEncoders(elementsRelations, unsuportedEncoders);
	videoEncoders = optionsLoaderFromXml.loadVideoEncoders(elementsRelations, unsuportedEncoders);
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

Converter::UnsupportedEncoders ElementsDB::getUnsuprtedEncoders() const{
	return unsuportedEncoders;
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
