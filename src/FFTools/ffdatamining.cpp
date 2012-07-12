/*
 * ffdatamining.cpp
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#include "ffdatamining.h"
#include "../Tools/settings.h"
#include "../Process/processexecutor.h"

namespace FFTools {

FFDataMining::FFDataMining() : suportEncoders(NULL),
		encoderDetector("^ [ D]E([VAS])[ S][ D][ T][[:space:]]+([^[:space:]]+)[[:space:]]*(.+)$"){
}

FFDataMining::~FFDataMining() {}

bool FFDataMining::scan(AVBox::SupportedEncoders *encoders){
	//todo try catch
	std::string ffpath = Settings::getSettings()->getValue(Settings::FFPATH);

	std::list<std::string> args;

	args.push_back("-codecs");

	Process::Executor ffmpeg(ffpath, args);

	if(ffmpeg.waitForRunChild()){
		std::string err;
		//todo exception
		while(ffmpeg.getLog() >> err)
			std::cout<<err<<std::endl;
		return false;
	}

	suportEncoders = encoders;
	std::string line;
	while(ffmpeg.getStdOut() >> line){
		parseLine(line);
	}
	suportEncoders = NULL;
	return true;
}

void FFDataMining::parseLine(const std::string& line){
	RegexTools::Matcher mat = encoderDetector.getMatcher(line);
	if(mat.find()){
		AVBox::SupportedEncoders::EncoderFFData en;
		en.encoder = mat.getGroup(2);
		en.description = mat.getGroup(3);
		if(mat.getGroup(1) == "V"){
			en.type = AVBox::SupportedEncoders::VIDEO;
		}else if(mat.getGroup(1) == "A"){
			en.type = AVBox::SupportedEncoders::AUDIO;
		}else{
			en.type = AVBox::SupportedEncoders::SUBTITLE;
		}
		suportEncoders->addEncoder(en);
	}
}

} /* namespace FFTools */
