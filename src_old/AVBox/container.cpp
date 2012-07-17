/*
 * container.cpp
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#include "container.h"

namespace AVBox {

Container::Container(const std::string& name) {
	this->name = name;
}
Container::Container() {
	name = "";
}

Container::~Container() {}

void Container::addAVFormat(const AVFormat& format){
	avformats[format.getName()] = format;
}

//void Container::addAudioFormat(const AudioFormat& audio){
//	audioFormats[audio.getFormat()] = audio;
//}
//void Container::addVideoFormat(const VideoFormat& video){
//	videoFormats[video.getFormat()] = video;
//}
//std::list<std::string> Container::getVideoFormats(){
//	std::list<std::string> list;
//	std::map<std::string, VideoFormat>::const_iterator it;
//	for(it = videoFormats.begin(); it != videoFormats.end(); ++it){
//		list.push_back(it->first);
//	}
//	return list;
//}
//VideoFormat Container::getVideoFormat(const std::string& name){
//	return videoFormats[name];
//}
//AudioFormat Container::getAudioFormat(const std::string& name){
//	return audioFormats[name];
//}
//std::list<std::string> Container::getAudioFormats(const VideoFormat& vEncoder) {
//	std::list<std::string> list;
//	std::map<std::string, AudioFormat>::const_iterator it;
//	for(it = audioFormats.begin(); it != audioFormats.end(); ++it){
//		list.push_back(it->first);
//	}
//	return list;
//}
std::string Container::getName() const{
	return name;
}

} /* namespace AVBox */
