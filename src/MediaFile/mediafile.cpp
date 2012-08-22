/*
 * mediafile.cpp
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */

#include "mediafile.h"

#include "mediafilescanner.h"
#include <iostream> //todo remove
#include <unistd.h> //todo remove
#include "../helper.h"

namespace MediaFile {

const static std::string STATE_OK="OK";
const static std::string STATE_WAITING="waiting";
const static std::string STATE_PROCESSING="processing";
const static std::string STATE_INVALID="invalid file";

MediaFile::MediaFile(Path filePath,  int fileId) : filePath(filePath) ,fileId(fileId) {
	fileInfo.duration = -1;
	fileInfo.fileState = NOT_SET;
	fileInfo.startTime = -1;
	fileInfo.bitrate = "";
	set = false;
	valid = false;
	clearConvertStatus();
}
MediaFile::~MediaFile() {}

bool MediaFile::scanMediaFile(){
	if(!set){
		set = true;
		fileInfo.videos.clear();
		fileInfo.audios.clear();

		MediaFileScanner scanner(filePath);
		//todo error state
		if(scanner.getFinalStatus() == MediaFileScanner::OK_RESULT){
			valid = true;
			fileInfo.startTime = scanner.getStartTime();
			fileInfo.duration = scanner.getDuration();
			fileInfo.bitrate = scanner.getBitrate();
			//todo getmetadata
			auto videoStreams = scanner.getVideoStreams();
			for(auto stream : videoStreams){
				fileInfo.videos.push_back(stream);
			}
			auto audioStreams = scanner.getAudioStreams();
			for(auto stream : audioStreams){
				fileInfo.audios.push_back(stream);
			}
		}else{
			std::cout<<"Invaid file"<<std::endl;
			return false;
		}
		return true;
	}
	return false;
}
bool MediaFile::isSet(){
	return set;
}
bool MediaFile::isValid(){
	return valid;
}
MediaFile::FileInfo MediaFile::getFileInfo(){
	return fileInfo;
}
void MediaFile::setSettingsList(const Converter::ConvertSettingsList& settingsList){
	this->settingsList = settingsList;
}
void MediaFile::clearConvertStatus(){
	status = WAITING;
	fraction = 0;
	remainingTime = -1;
}
void MediaFile::convert(){
	if(valid){
		status = PROCESSING;
		for(int i = 0; i < 10; i++){
			usleep(1000000);
			fraction += 0.1;
			std::cerr<<"File: "<<filePath.getPath()<<" fraction: "<<fraction<<std::endl;
		}
		status = FINISH;
	}else{
		status = INVALID_FILE;
	}
}
std::string MediaFile::getShortName(){
	return filePath.getLastPathPart().substr(0, 30);
}
std::string MediaFile::getRemainingTime(){
	return toS(remainingTime);				//todo rewrite to hh:mm:ss
}
int MediaFile::getPercentage(){
	return (fraction)*100+0.5;
}
std::string MediaFile::getConvertState(){
	switch(status){
	case WAITING: return STATE_WAITING;
	case PROCESSING: return STATE_PROCESSING;
	case FINISH: return STATE_OK;
	default: return STATE_INVALID;
	}
	return STATE_INVALID;
}
int MediaFile::getFileId(){
	return fileId;
}
bool MediaFile::isEnded(){
	return (status == FINISH) || (status == INVALID_FILE);
}
//void MediaFile::setMetadata(std::string key, std::string value){
//	metadata[key] = value;
//}

} /* namespace MediaFile */
