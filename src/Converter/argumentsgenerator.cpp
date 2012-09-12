/*
 * argumentsgenerator.cpp
 *
 *  Created on: 10.9.2012
 *      Author: martin
 */

#include "argumentsgenerator.h"
#include "../helper.h"

namespace Converter {

ArgumentsGenerator::ArgumentsGenerator(){
	numOfThreads = 1;
	isFileThreading = false;
}

void ArgumentsGenerator::setProfile(const Profile::Profile& actualProfile){
	this->actualProfile = actualProfile;
}
void ArgumentsGenerator::setThreading(const bool& enableFileThreading, const int& numOfThreads){
	isFileThreading = enableFileThreading;
	this->numOfThreads = numOfThreads;
}
std::list<std::string> ArgumentsGenerator::generate(){
	std::list<std::string> args;

	if(isFileThreading){
		args.push_back("-threads");
		args.push_back(toS(numOfThreads));
	}
	int mode;
	if(actualProfile.getVideoMode(mode)){
		if(mode == 0){
			args.push_back("-vcodec");
			args.push_back("copy");
		}
		if(mode == 1){
			generateVideo(args);
		}
		if(mode == 2){
			args.push_back("-vn");
		}
	}else{
		args.push_back("-vn");
	}
	if(actualProfile.getAudioMode(mode)){
		if(mode == 0){
			args.push_back("-acodec");
			args.push_back("copy");
		}
		if(mode == 1){
			generateAudio(args);
		}
		if(mode == 2){
			args.push_back("-an");
		}
	}else{
		args.push_back("-an");
	}
	std::list<Profile::Profile::ManualSettings> manualSettings;
	actualProfile.getManualSettings(manualSettings);
	for(auto setting : manualSettings){
		args.push_back(setting.command);
		for(auto item : setting.args){
			args.push_back(item);
		}
	}

	return args;
}
void ArgumentsGenerator::generateVideo(std::list<std::string>& args){
	MediaElement::Encoder encoder;
	if(actualProfile.getVideoEncoder(encoder)){
		args.push_back("-vcodec");
		args.push_back(encoder.getName());
	}
	MediaElement::Bitrate bitrate;
	if(actualProfile.getVideoBitrate(bitrate)){
		//todo min and max
		args.push_back("-vb");
		args.push_back(toS(bitrate.getValue())+"k");
	}
	MediaElement::Framerate framerate;
	if(actualProfile.getVideoFramerate(framerate) && !framerate.isOriginal()){
		args.push_back("-r");
		args.push_back(toS(framerate.getValue()));
	}
	MediaElement::Resolution resolution;
	if(actualProfile.getVideoResolution(resolution) && !resolution.isOriginal()){
		auto resol = resolution.getValue();
		args.push_back("-s");
		args.push_back(toS(resol.first)+"x"+toS(resol.second));
	}
	MediaElement::FFpreset ffpreset;
	if(actualProfile.getVideoFFpreset(ffpreset)){
		MediaElement::FFpreset::FFType type = ffpreset.getType();
		if(type != MediaElement::FFpreset::DISABLE_FFTYPE){
			args.push_back("-fpre");
			args.push_back(ffpreset.getPath().getPath());
		}
	}
}
void ArgumentsGenerator::generateAudio(std::list<std::string>& args){
	MediaElement::Encoder encoder;
	if(actualProfile.getAudioEncoder(encoder)){
		args.push_back("-acodec");
		args.push_back(encoder.getName());
	}
	MediaElement::AudioGrade audioGrade;
	if(actualProfile.getAudioGrade(audioGrade)){
		if(audioGrade.getType() == MediaElement::AudioGrade::BITRATE_TYPE){
			args.push_back("-ab");
			args.push_back(toS(audioGrade.getValue())+"k");
		}else{
			args.push_back("-aq");
			args.push_back(toS(audioGrade.getValue()));
		}
	}
	MediaElement::Samplerate samplerate;
	if(actualProfile.getAudioSamplerate(samplerate) && !samplerate.isOriginal()){
		args.push_back("-ar");
		args.push_back(toS(samplerate.getValue()));
	}
	MediaElement::Channel channel;
	if(actualProfile.getAudioChannel(channel) && !channel.isOriginal()){
		args.push_back("-ac");
		args.push_back(toS(channel.getValue()));
	}
}
} /* namespace Converter */
