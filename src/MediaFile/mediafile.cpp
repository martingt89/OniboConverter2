/* ---------------------------------------------------------------------------
** Author: Martin Geier
** mediafile.cpp is part of OniboConverter2.
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

#include "mediafile.h"

#include "../Converter/convertparser.h"
#include "../helper.h"
#include "../userpreferences.h"
#include "../ProcessExecutor/process.h"
#include "../Converter/argumentsgenerator.h"

namespace MediaFile {

MediaFile::MediaFile(const Path& filePath,  const int& fileId) :
		mediaInfo(filePath), filePath(filePath) ,fileId(fileId), mediaConvert(new MediaConvert){
	mediaConvert->setPath(filePath);
}

MediaFile::~MediaFile() {}

MediaInfo& MediaFile::getMediaInfo(){
	return mediaInfo;
}
std::shared_ptr<MediaConvert> MediaFile::getMediaConvert(){
	return mediaConvert;
}
Path MediaFile::getPath() const {
	return filePath;
}

void MediaFile::setDestinationPath(const Path& destinationPath){
	this->destinationPath = destinationPath;
	mediaConvert->setDestination(destinationPath);
}

void MediaFile::setActualProfile(const Profile::Profile& profile){
	this->profile = profile;
	MediaElement::Container container;
	profile.getContainer(container);
	std::string containerName = container.getName();
	mediaConvert->setContainerName(containerName);
	Converter::ArgumentsGenerator generator;
	generator.setProfile(profile);
	mediaConvert->setGenerator(generator);
}

std::string MediaFile::getShortName(){
	return filePath.getLastPathPart().substr(0, 30);
}

int MediaFile::getFileId(){
	return fileId;
}

bool MediaFile::supportThreding() const{
	MediaElement::Encoder encoder;
	if(profile.getVideoEncoder(encoder)){
		return encoder.isSupportedThreading();
	}
	return false;
}

void MediaFile::convert(bool enableFileThreading, int numberOfThreads){
	MediaElement::Container container;
	profile.getContainer(container);
	std::string containerName = container.getName();
	double duration = mediaInfo.getDuration();
	bool valid = (mediaInfo.getScanStatus() == MediaInfo::OK);
	mediaConvert->convert(enableFileThreading, numberOfThreads, valid, duration);
}

} /* namespace MediaFile */
