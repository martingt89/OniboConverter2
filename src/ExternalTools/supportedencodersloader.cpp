/*
 * encodersparser.cpp
 *
 *  Created on: 14.7.2012
 *      Author: martint
 */

#include "supportedencodersloader.h"

namespace ExternalTools {

SupportedEncodersLoader::SupportedEncodersLoader():
	encoderDetector("^ [ D]E([VAS])[ S][ D][ T][[:space:]]+([^[:space:]]+)[[:space:]]*(.+)$"){

}

SupportedEncodersLoader::~SupportedEncodersLoader() {}

bool SupportedEncodersLoader::scan(ConverterOptions::SupportedEncoders& encoders, const Path& ffmpegPath){
	std::list<std::string> args;
	args.push_back("-codecs");
	ProcessExecutor::Process ffmpeg(ffmpegPath.getPath(), args);

	if(ffmpeg.waitForProcessBegin()){
		std::string message = getExecutorError(ffmpeg);
		std::cerr<<message<<std::endl;	//todo add loging
		return false;
	}

	std::string line;
	bool findMatch = false;
	while(ffmpeg.getStdOut() >> line){
		parseLine(line, encoders, findMatch);
	}
	return findMatch & (ffmpeg.waitForProcessEnd() == 0);
}


void SupportedEncodersLoader::parseLine(const std::string& line,
		ConverterOptions::SupportedEncoders& encoders, bool& findMatch){
	RegexTools::Matcher mat = encoderDetector.getMatcher(line);
	if(mat.find()){
		findMatch = true;
//		ConverterOptions::Encoder::Type type;
//		std::string codecType = getCodecType(mat);
//		if (codecType == "V") {
//			type = AVBox::Encoder::VIDEO;
//		}else
//		if(codecType == "A"){
//			type = AVBox::Encoder::AUDIO;
//		}else{
//			type = AVBox::Encoder::UNKNOWN;
//		}

		encoders.addEncoder(getEncoderName(mat), getCodecDescription(mat));
	}
}

std::string SupportedEncodersLoader::getCodecType(const RegexTools::Matcher& mat) {
	return mat.getGroup(1);
}

std::string SupportedEncodersLoader::getEncoderName(const RegexTools::Matcher& mat) {
	return mat.getGroup(2);
}

std::string SupportedEncodersLoader::getCodecDescription(const RegexTools::Matcher& mat) {
	return mat.getGroup(3);
}

std::string SupportedEncodersLoader::getExecutorError(ProcessExecutor::Process& ffmpeg) {
	std::string err;
	std::string errorMessage = "";
	while (ffmpeg.getLog() >> err){
		errorMessage += err;
	}
	return errorMessage;
}
} /* namespace ExternalTools */
