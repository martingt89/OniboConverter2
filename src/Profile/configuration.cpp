/* ---------------------------------------------------------------------------
** Author: Martin Geier
** configuration.cpp is part of OniboConverter2.
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

#include "configuration.h"
#include "../helper.h"
#include <algorithm>
namespace Profile {

Configuration::Configuration(MediaElement::ElementsDB elementsDb) : elementsDb(elementsDb){}

Configuration::Configuration(const Profile& profile, MediaElement::ElementsDB elementsDb) : elementsDb(elementsDb){
	this->addProperty(NAME_OPT, profile.getName());
	MediaElement::Container container;
	if(profile.getContainer(container)){
		this->addProperty(CONTAINER_OPT, container.getName());
	}
	int row;
	if(profile.getVideoMode(row)){
		this->addProperty(VIDEO_MODE_OPT, toS(row));
	}
	MediaElement::Format videoFormat;
	if(profile.getVideoFormat(videoFormat)){
		this->addProperty(VIDEO_FORMAT_OPT, videoFormat.getName());
	}
	MediaElement::Encoder videoEncoder;
	if(profile.getVideoEncoder(videoEncoder)){
		this->addProperty(VIDEO_ENCODER_OPT, videoEncoder.getName());
	}
	MediaElement::Framerate framerate;
	if(profile.getVideoFramerate(framerate)){
		this->addProperty(VIDEO_FRAMERATE_OPT, toS(framerate.getValue()));
	}
	MediaElement::Bitrate bitrate;
	if(profile.getVideoBitrate(bitrate)){
		this->addProperty(VIDEO_BITRATE_OPT, toS(bitrate.getValue()));
		this->addProperty(VIDEO_BITRATE_MIN_OPT, toS(bitrate.getMinBitrate()));
		this->addProperty(VIDEO_BITRATE_MAX_OPT, toS(bitrate.getMaxBitrate()));
	}
	MediaElement::Resolution resolution;
	if(profile.getVideoResolution(resolution)){
		this->addProperty(VIDEO_RESOLUTION_X_OPT, toS(resolution.getValue().first));
		this->addProperty(VIDEO_RESOLUTION_Y_OPT, toS(resolution.getValue().second));
		this->addProperty(VIDEO_RESOLUTION_ASP_OPT, resolution.getAspectRatio().getXcolonY());
		this->addProperty(VIDEO_RESOLUTION_NAME_OPT, resolution.getName());
	}
	MediaElement::FFpreset ffpreset;
	if(profile.getVideoFFpreset(ffpreset)){
		this->addProperty(VIDEO_FFPRESET_PREFIX_OPT, ffpreset.getPrefix());
		if(ffpreset.getType() == MediaElement::FFpreset::BUILDIN_FFTYPE){
			this->addProperty(VIDEO_FFPRESET_PATH_OPT, ffpreset.getPath().getLastPathPart());
		}else{
			this->addProperty(VIDEO_FFPRESET_PATH_OPT, ffpreset.getPath().getPath());
		}
		this->addProperty(VIDEO_FFPRESET_TYPE_OPT, toS((int)ffpreset.getType()));
	}

	if(profile.getAudioMode(row)){
		this->addProperty(AUDIO_MODE_OPT, toS(row));
	}
	MediaElement::Format audioFormat;
	if(profile.getAudioFormat(audioFormat)){
		this->addProperty(AUDIO_FORMAT_OPT, audioFormat.getName());
	}
	MediaElement::Encoder audioEncoder;
	if(profile.getAudioEncoder(audioEncoder)){
		this->addProperty(AUDIO_ENCODER_OPT, audioEncoder.getName());
	}
	MediaElement::AudioGrade audioGrade;
	if(profile.getAudioGrade(audioGrade)){
		this->addProperty(AUDIO_GRADE_TYPE_OPT, toS(audioGrade.getType()));
		this->addProperty(AUDIO_GRADE_VALUE_OPT, toS(audioGrade.getValue()));
	}
	MediaElement::Samplerate samplerate;
	if(profile.getAudioSamplerate(samplerate)){
		this->addProperty(AUDIO_SAMPLERATE_OPT, toS(samplerate.getValue()));
	}
	MediaElement::Channel channel;
	if(profile.getAudioChannel(channel)){
		this->addProperty(AUDIO_CHANNEL_VALUE_OPT, toS(channel.getValue()));
		this->addProperty(AUDIO_CHANNEL_NAME_OPT, channel.getName());
	}
	std::list<Profile::ManualSettings> manualSettings;
	profile.getManualSettings(manualSettings);
	for(auto setting : manualSettings){
		this->addProperty(MANUAL_COMMAND_OPT, setting.command);
		for(auto item : setting.args){
			this->addProperty(MANUAL_ARG_OPT, item);
		}
	}
}

Configuration::~Configuration() {}

void Configuration::addProperty(const Options& options, const std::string& propertie){
	if(options == MANUAL_COMMAND_OPT || options == MANUAL_ARG_OPT){
		if(options == MANUAL_COMMAND_OPT){
			Profile::ManualSettings set;
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
std::string Configuration::getProperty(const Options& options) const{
	return optionsToValue.get(options);
}
std::string Configuration::getName() const{
	return optionsToValue.get(NAME_OPT);
}
bool Configuration::getContainer(MediaElement::Container& container) const{
	bool isName;
	std::string cName = optionsToValue.get(CONTAINER_OPT, isName);
	return (isName && elementsDb.getContainers().getContainerByName(cName, container));
}
bool Configuration::getVideoMode(int& row) const{		//todo object
	bool exist;
	row = toN(optionsToValue.get(VIDEO_MODE_OPT, exist),int());
	return exist;
}
bool Configuration::getVideoFormat(MediaElement::Format& videoFormat) const{
	bool isName;
	std::string videoFormatName = optionsToValue.get(VIDEO_FORMAT_OPT, isName);
	videoFormat = MediaElement::Format(videoFormatName, MediaElement::Format::FORMAT_TYPE_VIDEO);
	return isName;
}
bool Configuration::getVideoEncoder(MediaElement::Encoder& videoEncoder) const{
	bool exist;
	std::string videoEncoderName = optionsToValue.get(VIDEO_ENCODER_OPT, exist);
	return (exist && elementsDb.getVideoEncoders().getEncoderByName(videoEncoderName, videoEncoder));
}
bool Configuration::getVideoBitrate(MediaElement::Bitrate& videoBitrate) const{
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
	videoBitrate = MediaElement::Bitrate(bitrate, bitrateMin, bitrateMax);
	return true;
}
bool Configuration::getVideoResolution(MediaElement::Resolution& resolution) const{
	bool exist;
	int x = toN(optionsToValue.get(VIDEO_RESOLUTION_X_OPT, exist), int());
	if(x == -1){
		return true;
	}
	if(!exist){
		return false;
	}
	int y = toN(optionsToValue.get(VIDEO_RESOLUTION_Y_OPT, exist), int());
	std::string name = optionsToValue.get(VIDEO_RESOLUTION_NAME_OPT, exist);
	std::string aspect = optionsToValue.get(VIDEO_RESOLUTION_ASP_OPT, exist);

	resolution = MediaElement::Resolution(name, MediaElement::AspectRatio::createFromString(aspect), x, y);
	return true;
}
bool Configuration::getVideoFFpreset(MediaElement::FFpreset& ffpreset) const{
	bool exist = true;

	int type = toN(optionsToValue.get(VIDEO_FFPRESET_TYPE_OPT, exist), int());
	if(!exist){
		return false;
	}
	MediaElement::FFpreset::FFType fftype = (MediaElement::FFpreset::FFType)type;
	if(fftype == MediaElement::FFpreset::DISABLE_FFTYPE){
		ffpreset = MediaElement::FFpreset(std::string(), std::string(), fftype);
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

	ffpreset = MediaElement::FFpreset(ffFilePath, prefix, fftype);
	return true;
}
bool Configuration::getVideoFramerate(MediaElement::Framerate& framerate) const{
	bool exist;
	double frame = toN(optionsToValue.get(VIDEO_FRAMERATE_OPT, exist), double());
	framerate = MediaElement::Framerate(frame);
	return exist;
}
//
bool Configuration::getAudioMode(int& row) const{
	bool exist = false;
	row = toN(optionsToValue.get(AUDIO_MODE_OPT, exist), int());
	return exist;
}
bool Configuration::getAudioFormat(MediaElement::Format& audioFormat) const{
	bool exist = false;
	std::string audioFormatName = optionsToValue.get(AUDIO_FORMAT_OPT, exist);
	audioFormat = MediaElement::Format(audioFormatName, MediaElement::Format::FORMAT_TYPE_AUDIO);
	return exist;
}
bool Configuration::getAudioEncoder(MediaElement::Encoder& audioEncoder) const{
	bool exist = false;
	std::string audioEncoderName = optionsToValue.get(AUDIO_ENCODER_OPT, exist);
	return (exist && elementsDb.getAudioEncoders().getEncoderByName(audioEncoderName, audioEncoder));
}
bool Configuration::getAudioGrade(MediaElement::AudioGrade& audioGrade) const{
	bool exist = false;
	int value = toN(optionsToValue.get(AUDIO_GRADE_VALUE_OPT, exist), int());
	MediaElement::AudioGrade::Type gradeType =
			(MediaElement::AudioGrade::Type)toN(optionsToValue.get(AUDIO_GRADE_VALUE_OPT, exist), int());
	audioGrade = MediaElement::AudioGrade(value, gradeType);
	return exist;
}
bool Configuration::getAudioSamplerate(MediaElement::Samplerate& audioSamplerate) const{
	bool exist = false;
	int samplerate = toN(optionsToValue.get(AUDIO_SAMPLERATE_OPT, exist), int());
	audioSamplerate = MediaElement::Samplerate(samplerate);
	return exist;
}
bool Configuration::getAudioChannel(MediaElement::Channel& audioChannel) const{
	bool exist = false;
	int numOfChannel = toN(optionsToValue.get(AUDIO_CHANNEL_VALUE_OPT, exist), int());
	if(!exist){
		return false;
	}
	if(numOfChannel < 0){
		return true;
	}
	std::string name = optionsToValue.get(AUDIO_CHANNEL_NAME_OPT, exist);
	if(!exist){
		return false;
	}
	audioChannel = MediaElement::Channel(name, numOfChannel);
	return true;
}
void Configuration::getManualSettings(std::list<Profile::ManualSettings>& manualSettings) const{
	manualSettings = this->settings;
}

Profile Configuration::getProfile() const{
	Profile profile(getName());

	MediaElement::Container container;
	if(getContainer(container)){
		profile.setContainer(container);
	}
	int row;
	if(getVideoMode(row)){
		profile.setVideoMode(row);
	}
	MediaElement::Format videoFormat;
	if(getVideoFormat(videoFormat)){
		profile.setVideoFormat(videoFormat);
	}
	MediaElement::Encoder videoEncoder;
	if(getVideoEncoder(videoEncoder)){
		profile.setVideoEncoder(videoEncoder);
	}
	MediaElement::Bitrate videoBitrate;
	if(getVideoBitrate(videoBitrate)){
		profile.setVideoBitrate(videoBitrate);
	}
	MediaElement::Resolution resolution;
	if(getVideoResolution(resolution)){
		profile.setVideoResolution(resolution);
	}
	MediaElement::FFpreset ffpreset;
	if(getVideoFFpreset(ffpreset)){
		profile.setVideoFFpreset(ffpreset);
	}
	MediaElement::Framerate framerate;
	if(getVideoFramerate(framerate)){
		profile.setVideoFramerate(framerate);
	}
	//
	if(getAudioMode(row)){
		profile.setAudioMode(row);
	}
	MediaElement::Format audioFormat;
	if(getAudioFormat(audioFormat)){
		profile.setAudioFormat(audioFormat);
	}
	MediaElement::Encoder audioEncoder;
	if(getAudioEncoder(audioEncoder)){
		profile.setAudioEncoder(audioEncoder);
	}
	MediaElement::AudioGrade audioGrade;
	if(getAudioGrade(audioGrade)){
		profile.setAudioGrade(audioGrade);
	}
	MediaElement::Samplerate audioSamplerate;
	if(getAudioSamplerate(audioSamplerate)){
		profile.setAudioSamplerate(audioSamplerate);
	}
	MediaElement::Channel audioChannel;
	if(getAudioChannel(audioChannel)){
		profile.setAudioChannel(audioChannel);
	}
	//
	std::list<Profile::ManualSettings> manualSettings;
	getManualSettings(manualSettings);
	profile.setManualSettings(manualSettings);
	return profile;
}

} /* namespace Profile */
