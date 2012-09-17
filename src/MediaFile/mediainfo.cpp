/* ---------------------------------------------------------------------------
** Author: Martin Geier
** mediainfo.cpp is part of OniboConverter2.
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

//todo getmetadata

#include "mediainfo.h"
#include "mediascanner.h"

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

	MediaScanner scanner(mediaPath);
	if(scanner.getFinalStatus() == MediaScanner::OK_RESULT){
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
			//std::cout<<"audio stream: "<<stream.getStreamNumber().second<<std::endl;
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
