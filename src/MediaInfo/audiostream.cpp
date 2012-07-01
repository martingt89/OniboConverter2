/*
 * audiostream.cpp
 *
 *  Created on: 20.6.2012
 *      Author: martint
 */

#include "audiostream.h"

namespace MediaInfo {

AudioStream::AudioStream(int f, int r): Stream(f,r){

}

void AudioStream::setValue(Audio name, std::string value){
	content[name] = value;
}
std::string AudioStream::getValue(Audio name){
	std::map<Audio, std::string>::iterator it = content.find(name);
	if(it != content.end()){
		return it->second;
	}
	return "";
}

} /* namespace MediaInfo */
