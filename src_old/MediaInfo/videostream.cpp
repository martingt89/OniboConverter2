/*
 * videostream.cpp
 *
 *  Created on: 20.6.2012
 *      Author: martint
 */

#include "videostream.h"

namespace MediaInfo {

MediaInfo::VideoStream::VideoStream(int f, int r) : Stream(f,r){

}

void MediaInfo::VideoStream::setValue(Video name, std::string value){
	content[name] = value;
}

std::string MediaInfo::VideoStream::getValue(Video name){
	std::map<Video, std::string>::iterator it = content.find(name);
	if(it != content.end()){
		return it->second;
	}
	return "";
}
} /* namespace MediaInfo */
