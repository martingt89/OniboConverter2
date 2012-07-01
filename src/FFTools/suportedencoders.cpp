/*
 * suportedencoders.cpp
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#include "suportedencoders.h"
#include "../settings.h"
#include "../Process/processexecutor.h"

namespace FFTools {

SuportedEncoders::SuportedEncoders() :
		encoderDetector("^ [ D]E([VAS])[ S][ D][ T][[:space:]]+([^[:space:]]+)[[:space:]]*(.+)$"){
	rescan();
}

SuportedEncoders::~SuportedEncoders() {}

bool SuportedEncoders::isSuported(const std::string& name, std::string& description) const {
	std::map<std::string, Encoder>::const_iterator it;
	if((it = suportedEndcoders.find(name)) != suportedEndcoders.end()){
		description = it->second.description;
		return true;
	}
	return false;
}

void SuportedEncoders::rescan(){
	//todo try catch
	std::string ffpath = Settings::getSettings()->getValue(Settings::FFPATH);

	suportedEndcoders.clear();

	std::list<std::string> args;

	args.push_back("-codecs");

	Process::Executor ffmpeg(ffpath, args);

	if(ffmpeg.waitForRunChild()){
		std::string err;
		//exception
		while(ffmpeg.getLog() >> err)
			std::cout<<err<<std::endl;
		return;
	}
	std::string line;
	while(ffmpeg.getStdOut() >> line){
		parseLine(line);
	}
}

void SuportedEncoders::parseLine(const std::string& line){
	RegexTools::Matcher mat = encoderDetector.getMatcher(line);
	if(mat.find()){
		Encoder en;
		en.encoder = mat.getGroup(2);
		en.description = mat.getGroup(3);
		if(mat.getGroup(1) == "V"){
			en.type = VIDEO;
		}else if(mat.getGroup(1) == "A"){
			en.type = AUDIO;
		}else{
			en.type = SUBTITLE;
		}
		suportedEndcoders[en.encoder] = en;
	}
}

} /* namespace FFTools */
