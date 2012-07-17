/*
 * encodersparser.cpp
 *
 *  Created on: 14.7.2012
 *      Author: martint
 */

#include "encodersparser.h"
#include "../Tools/settings.h"


namespace FFTools {

EncodersParser::EncodersParser(){
	encoderDetector = new RegexTools::Regex
			("^ [ D]E([VAS])[ S][ D][ T][[:space:]]+([^[:space:]]+)[[:space:]]*(.+)$");

	std::string ffpath = Settings::getSettings()->getValue(Settings::FFPATH);

	std::list<std::string> args;
	args.push_back("-codecs");
	Process::Executor ffmpeg(ffpath, args);

	if(ffmpeg.waitForRunChild()){
		std::string message = getExecutorError(ffmpeg);
		std::cerr<<message<<std::endl;	//todo add loging
		return;
	}

	std::string line;
	while(ffmpeg.getStdOut() >> line){
		parseLine(line);
	}
}

EncodersParser::~EncodersParser() {
	delete encoderDetector;
}

std::list<AVBox::Encoder> EncodersParser::getEncoders() const{
	return encoders;
}

void EncodersParser::parseLine(const std::string& line){
	RegexTools::Matcher mat = encoderDetector->getMatcher(line);
	if(mat.find()){
		AVBox::Encoder::Type type;
		std::string codecType = getCodecType(mat);
		if (codecType == "V") {
			type = AVBox::Encoder::VIDEO;
		}else
		if(codecType == "A"){
			type = AVBox::Encoder::AUDIO;
		}else{
			type = AVBox::Encoder::UNKNOWN;
		}
		AVBox::Encoder encoder(getEncoderName(mat), getCodecDescription(mat), type);
		encoders.push_back(encoder);
	}
}

std::string EncodersParser::getCodecType(const RegexTools::Matcher& mat) {
	return mat.getGroup(1);
}

std::string EncodersParser::getEncoderName(const RegexTools::Matcher& mat) {
	return mat.getGroup(2);
}

std::string EncodersParser::getCodecDescription(const RegexTools::Matcher& mat) {
	return mat.getGroup(3);
}

std::string EncodersParser::getExecutorError(Process::Executor& ffmpeg) {
	std::string err;
	std::string errorMessage = "";
	while (ffmpeg.getLog() >> err){
		errorMessage += err;
	}
	return errorMessage;
}
} /* namespace FFTools */
