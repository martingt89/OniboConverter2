/*
 * mediainfo.cpp
 *
 *  Created on: 20.6.2012
 *      Author: martint
 */

#include "mediafile.h"
#include "../helper.h"
#include <iostream>
namespace MediaInfo{

MediaFile::MediaFile(std::string filePath) : filePath(filePath) {
	duration = -1;
	fileState = NOT_SET;
	startTime = 0;
}
MediaFile::~MediaFile() {

}
std::string MediaFile::getFilePath(){
	return filePath;
}
void MediaFile::addVideoStream(VideoStream stream){
	videos.push_back(stream);
}
void MediaFile::addAudioStream(AudioStream stream){
	audios.push_back(stream);
}
void MediaFile::setDuration(double duration){
	this->duration = duration;
}
void MediaFile::setStartTime(double time){
	startTime = time;
}
void MediaFile::setBitrate(const std::string &bitrate){
	this->bitrate = bitrate;
}
double MediaFile::getDuration(){
	return duration;
}
double MediaFile::getStartTime(){
	return startTime;
}
std::string MediaFile::getBitrate(){
	return bitrate;
}
void MediaFile::setState(State state){
	fileState = state;
}
MediaFile::State MediaFile::getState(){
	return fileState;
}
VideoStream MediaFile::getVideoStream(unsigned int index) throw(std::out_of_range){
	if(index >= videos.size())
		throw std::out_of_range (std::string("element count: ")+videos.size()+" requested index: "+index);
	return videos[index];
}
int MediaFile::getVideoStreamCaunt(){
	return videos.size();
}
AudioStream MediaFile::getAudioStream(int index){
	return audios[index];
}
int MediaFile::getAudioStreamCaunt(){
	return audios.size();
}
void MediaFile::setMetadata(std::string key, std::string value){
	metadata[key] = value;
}

}
