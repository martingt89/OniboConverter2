/*
 * mediainfo.cpp
 *
 *  Created on: 13.9.2012
 *      Author: martin
 */

//todo getmetadata

#include "mediainfo.h"
#include "mediafilescanner.h"

namespace MediaFile {

MediaInfo::MediaInfo(const Path& mediaPath) : mediaPath(mediaPath){
	scanStatus = NOSCAN;
	duration = -1;
	startTime = -1;
	bitrate = "";
}

MediaInfo::~MediaInfo() {}

MediaInfo::ScanStatus MediaInfo::scanMediaFile(){
	videos.clear();
	audios.clear();

	MediaFileScanner scanner(mediaPath);
	if(scanner.getFinalStatus() == MediaFileScanner::OK_RESULT){
		scanStatus = OK;
		startTime = scanner.getStartTime();
		duration = scanner.getDuration();
		bitrate = scanner.getBitrate();
		auto videoStreams = scanner.getVideoStreams();
		for(auto stream : videoStreams){
			videos.push_back(stream);
		}
		auto audioStreams = scanner.getAudioStreams();
		for(auto stream : audioStreams){
			audios.push_back(stream);
		}
	}else{
		scanStatus = INVALID;
	}
	return scanStatus;
}

double MediaInfo::getDuration() const{
	return duration;
}
double MediaInfo::getStartTime() const{
	return startTime;
}
std::string MediaInfo::getBitrate() const{
	return bitrate;
}
std::vector<VideoStream> MediaInfo::getVideoStreams() const{
	return videos;
}
std::vector<AudioStream> MediaInfo::getAudioStreams() const{
	return audios;
}
MediaInfo::ScanStatus MediaInfo::getScanStatus() const{
	return scanStatus;
}
//void MediaFile::setMetadata(std::string key, std::string value){
//	metadata[key] = value;
//}
} /* namespace MediaFile */
