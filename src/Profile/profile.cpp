/*
 * profil.cpp
 *
 *  Created on: 29.7.2012
 *      Author: martint
 */

#include "profile.h"
#include "../helper.h"

namespace Profile {

Profile::Profile() {}

Profile::~Profile() {}

void Profile::addProperty(const Options& options, const std::string& propertie){
	optionsToValue.set(options, propertie);
}
//
std::string Profile::getName() const{
	return optionsToValue.get(NAME_OPT);
}
//
bool Profile::getContainerName(std::string& containerName) const{
	bool exist;
	containerName = optionsToValue.get(CONTAINER_OPT, exist);
	return exist;
}
bool Profile::getVideoMode(int& row) const{
	bool exist;
	row = toN(optionsToValue.get(VIDEO_MODE_OPT, exist),int());
	return exist;
}
bool Profile::getVideoFormatName(std::string& videoFormatName) const{
	bool exist;
	videoFormatName = optionsToValue.get(VIDEO_FORMAT_OPT, exist);
	return exist;
}
bool Profile::getVideoEncoderName(std::string& videoEncoderName) const{
	bool exist;
	videoEncoderName = optionsToValue.get(VIDEO_ENCODER_OPT, exist);
	return exist;
}
bool Profile::getVideoBitrate(ConverterOptions::Bitrate& videoBitrate) const{
	bool exist;
	int bitrate = toN(optionsToValue.get(VIDEO_BITRATE_OPT, exist), int());
	if(!exist){
		return false;
	}
	int bitrateMin = toN(optionsToValue.get(VIDEO_BITRATE_MIN_OPT, exist), int());
	if(!exist){
		bitrateMin = -1;
	}
	int bitrateMax = toN(optionsToValue.get(VIDEO_BITRATE_MAX_OPT, exist), int());
	if(!exist){
		bitrateMax = -1;
	}
	videoBitrate = ConverterOptions::Bitrate(bitrate, bitrateMin, bitrateMax);
	return true;
}
bool Profile::getVideoResolution(ConverterOptions::Resolution& resolution, bool& original) const{
	original = false;
	bool exist;
	int x = toN(optionsToValue.get(VIDEO_RESOLUTION_X_OPT, exist), int());
	if(x == -1){
		original = true;
		return true;
	}
	if(!exist){
		return false;
	}
	int y = toN(optionsToValue.get(VIDEO_RESOLUTION_Y_OPT, exist), int());
	std::string name = optionsToValue.get(VIDEO_RESOLUTION_NAME_OPT, exist);
	std::string aspect = optionsToValue.get(VIDEO_RESOLUTION_ASP_OPT, exist);
	resolution = ConverterOptions::Resolution(name, aspect, x, y);
	return true;
}
//bool getFFpreset(ConverterOptions::FFpreset&)
bool Profile::getVideoFramerate(ConverterOptions::Framerate& framerate, bool& original) const{
	bool exist;
	original = false;
	double frame = toN(optionsToValue.get(VIDEO_FRAMERATE_OPT, exist), double());
	if(frame == -1){
		original = true;
	}
	framerate = ConverterOptions::Framerate(frame);
	return exist;
}
//
bool Profile::getAudioMode(int& row) const{
	row = 0;
	return true;
}
} /* namespace Profile */
