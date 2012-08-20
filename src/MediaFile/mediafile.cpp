/*
 * mediafile.cpp
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */

#include "mediafile.h"

#include "mediafilescanner.h"
#include <iostream> //todo remove
namespace MediaFile {

MediaFile::MediaFile(Path filePath) : filePath(filePath) {
	duration = -1;
	fileState = NOT_SET;
	startTime = -1;
	bitrate = "";
	set = false;
	valid = false;
}
MediaFile::~MediaFile() {}

bool MediaFile::scanMediaFile(){
	if(!set){
		set = true;
		videos.clear();
		audios.clear();

		MediaFileScanner scanner(filePath);
		//todo error state
		if(scanner.getFinalStatus() == MediaFileScanner::OK_RESULT){
			valid = true;
			startTime = scanner.getStartTime();
			duration = scanner.getDuration();
			bitrate = scanner.getBitrate();
			//todo getmetadata
			auto videoStreams = scanner.getVideoStreams();
			for(auto stream : videoStreams){
				videos.push_back(stream);
			}
			auto audioStreams = scanner.getAudioStreams();
			for(auto stream : audioStreams){
				audios.push_back(stream);
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
//std::string MediaFile::getFilePath(){
//	return filePath;
//}

double MediaFile::getDuration(){
	return duration;
}
double MediaFile::getStartTime(){
	return startTime;
}
std::string MediaFile::getBitrate(){
	return bitrate;
}
MediaFile::State MediaFile::getState(){
	return fileState;
}
VideoStream MediaFile::getVideoStream(unsigned int index) throw(std::out_of_range){
//	if(index >= videos.size())	TODO fix
//		throw std::out_of_range (std::string("element count: ")<<videos.size()<<" requested index: "<<index);
	return videos[index];
}
int MediaFile::getNumberOfVideoStreams(){
	return videos.size();
}
AudioStream MediaFile::getAudioStream(int index){
	return audios[index];
}
int MediaFile::getNumberOfAudioStreams(){
	return audios.size();
}
//void MediaFile::setMetadata(std::string key, std::string value){
//	metadata[key] = value;
//}

} /* namespace MediaFile */
