/*
 * mediafile.cpp
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */


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
