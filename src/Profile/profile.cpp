/*
 * profil.cpp
 *
 *  Created on: 29.7.2012
 *      Author: martint
 */

#include "profile.h"
#include "../helper.h"
#include <algorithm>
namespace Profile {

Profile::Profile(){

}

Profile::~Profile() {}

void Profile::addProperty(const Options& options, const std::string& propertie){
	if(options == MANUAL_COMMAND_OPT || options == MANUAL_ARG_OPT){
		if(options == MANUAL_COMMAND_OPT){
			ManualSettings set;
			set.command = propertie;
			settings.push_front(set);
		}else{
			if(settings.begin() != settings.end()){
				settings.begin()->args.push_back(propertie);
			}
		}
	}else{
		optionsToValue.set(options, propertie);
	}
}
std::string Profile::getProperty(const Options& options) const{
	return optionsToValue.get(options);
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
	videoBitrate = ConverterOptions::Bitrate(
			bitrate, ConverterOptions::Bitrate::VIDEO, bitrateMin, bitrateMax);
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
bool Profile::getVideoFFpreset(ConverterOptions::FFpreset& ffpreset) const{
	bool exist = true;

	int type = toN(optionsToValue.get(VIDEO_FFPRESET_TYPE_OPT, exist), int());
	if(!exist){
		return false;
	}
	ConverterOptions::FFpreset::FFType fftype = (ConverterOptions::FFpreset::FFType)type;
	if(fftype == ConverterOptions::FFpreset::DISABLE_FFTYPE){
		ffpreset = ConverterOptions::FFpreset(std::string(), std::string(), fftype);
		return true;
	}
	std::string path = optionsToValue.get(VIDEO_FFPRESET_PATH_OPT, exist);
	if(!exist){
		return false;
	}
	Path ffFilePath(path);
	std::string prefix = optionsToValue.get(VIDEO_FFPRESET_PREFIX_OPT, exist);
	if(!exist){
		return false;
	}

	ffpreset = ConverterOptions::FFpreset(ffFilePath, prefix, fftype);
	return true;
}
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
	bool exist = false;
	row = toN(optionsToValue.get(AUDIO_MODE_OPT, exist), int());
	return exist;
}
bool Profile::getAudioFormatName(std::string& audioFormatName) const{
	bool exist = false;
	audioFormatName = optionsToValue.get(AUDIO_FORMAT_OPT, exist);
	return exist;
}
bool Profile::getAudioEncoderName(std::string& audioEncoderName) const{
	bool exist = false;
	audioEncoderName = optionsToValue.get(AUDIO_ENCODER_OPT, exist);
	return exist;
}
bool Profile::getAudioBitrate(ConverterOptions::Bitrate& audioBitrate) const{
	bool exist = false;
	int bitrate = toN(optionsToValue.get(AUDIO_BITRATE_OPT, exist), int());
	audioBitrate = ConverterOptions::Bitrate(bitrate, ConverterOptions::Bitrate::AUDIO);
	return exist;
}
bool Profile::getAudioSamplerate(ConverterOptions::Samplerate& audioSamplerate, bool& isOriginal) const{
	isOriginal = false;
	bool exist = false;
	int samplerate = toN(optionsToValue.get(AUDIO_SAMPLERATE_OPT, exist), int());
	if(samplerate < 0){
		isOriginal = true;
	}
	audioSamplerate = ConverterOptions::Samplerate(samplerate);
	return exist;
}
bool Profile::getAudioChannel(ConverterOptions::Channel& audioChannel, bool& isOriginal) const{
	isOriginal = false;
	bool exist = false;
	int numOfChannel = toN(optionsToValue.get(AUDIO_CHANNEL_VALUE_OPT, exist), int());
	if(!exist){
		return false;
	}
	if(numOfChannel < 0){
		isOriginal = true;
		return true;
	}
	std::string name = optionsToValue.get(AUDIO_CHANNEL_NAME_OPT, exist);
	if(!exist){
		return false;
	}
	audioChannel = ConverterOptions::Channel(name, numOfChannel);
	return true;
}
void Profile::getManualSettings(std::list<ManualSettings>& manualSettings) const{
	manualSettings = this->settings;
}
} /* namespace Profile */
