/*
 * infoloader.cpp
 *
 *  Created on: 26.6.2012
 *      Author: martint
 */

#include "infoloader.h"
#include "../settings.h"
#include "../Process/processexecutor.h"
#include <sstream>

namespace MediaInfo{

template<class T>
void strToNumber(const std::string &number, T &ret){
	std::stringstream ss;
	ss << number;
	ss >> ret;
}

bool trimBy(const std::string delimiter, const std::string &input, std::string &first, std::string &rest ){
	std::string::size_type pos = input.find(delimiter);
	if(pos == std::string::npos){
		return false;
	}
	first = input.substr(0, pos);
	rest = input.substr(pos+delimiter.size());
	return true;
}

InfoLoader::InfoLoader(std::string file):
		durationRegex("Duration: ([\\.:[:digit:]]+), start: ([\\.[:digit:]]+), bitrate: (.*)"),
		videoStreamRegex("Stream #(.+): Video: ([^,]+), ([^,]+), ([[:digit:]]+)x([[:digit:]]+)[^,]*,"),
		audioStreamRegex("Stream #(.+): Audio: ([^,]+), ([[:digit:]]+) Hz, ([^,]+), ([^,]+), ([^,]+)"),
		metadataRegex("^[[:space:]]{4}([^[:space:]]+)[^:]*:[[:space:]]*(.+)$"),
		mediaFile(file){
	this->file = file;
	parseState = State::START;
	//TODO try catch
	std::string path = Settings::getSettings()->getValue(Settings::FFPATH);

	std::list<std::string> args;

	args.push_back("-i");
	args.push_back(file);

	Process::Executor ex(path, args);

	if(ex.waitForRunChild() != 0){
		std::string messages;
		while(ex.getLog() >> messages){
			std::cout<<"Process::Executor error: "<<messages<<std::endl;
		}
		//todo excetion
		return;
	}
	std::string line;
	while(ex.getStdErr() >> line){
		parse(line);
	}
}

InfoLoader::~InfoLoader() {
}

MediaInfo::MediaFile InfoLoader::getMediaInfo(){
	return mediaFile;
}
void InfoLoader::parse(const std::string &line){
//	std::cout<<"parse: "<<line<<std::endl;
	if(parseState == START){
		if(line.find("Metadata:")){
			parseState = METADATA;
			return;
		}
	}else if(parseState == METADATA){
		RegexTools::Matcher m = metadataRegex.getMatcher(line);
		if(m.find()){
			mediaFile.setMetadata(m.getGroup(1), m.getGroup(2));
		}
	}
	if(parseState == START || parseState == METADATA){
		RegexTools::Matcher m = durationRegex.getMatcher(line);
		if(m.find()){
			parseState = DURATION;
			parseDuration(m);
		}else if(line.find(file+": Invalid data found") == 0){
			parseState = INVALID_DATA;
			mediaFile.setState(MediaInfo::MediaFile::INVALID_FORMAT);
		}else if(line.find(file+": No such file or directory") == 0){
			parseState = FILE_NOT_FOUND;
			mediaFile.setState(MediaInfo::MediaFile::NOT_FOUND);
		}
	}else if(parseState == DURATION){
		RegexTools::Matcher videoMatcher = videoStreamRegex.getMatcher(line);
		RegexTools::Matcher audioMatcher = audioStreamRegex.getMatcher(line);
		if(videoMatcher.find()){
			size_t start;
			size_t end;
			videoStreamRegex.search(line, start, end);
			parseVideoStream(videoMatcher, line.substr(end));
		}else if(audioMatcher.find()){
			parseAudioStream(audioMatcher);
		}else if(line == "At least one output file must be specified"){
			parseState = State::END;
			mediaFile.setState(MediaInfo::MediaFile::OK);
		}
	}
}

void InfoLoader::parseDuration(const RegexTools::Matcher &matcher){	//magic, don't touch this
	mediaFile.setBitrate(matcher.getGroup(3));
	double start;
	strToNumber(matcher.getGroup(2), start);
	mediaFile.setStartTime(start);
	std::string tmp = matcher.getGroup(1)+":";
	std::string first;
	std::string rest;
	double duration = 0;
	double number;
	while(trimBy(":", tmp, first, rest)){
		duration *= 60;
		strToNumber(first, number);
		duration += number;
		tmp = rest;
	}
	mediaFile.setDuration(duration);
}

void InfoLoader::parseVideoStream(const RegexTools::Matcher &matcher, const std::string& lineEnd){
	std::string first, rest;
	trimBy(".", matcher.getGroup(1), first, rest);
	int f,r;
	strToNumber(first, f);
	strToNumber(rest, r);

	VideoStream stream(f,r);
	stream.setValue(VideoStream::CODEC, matcher.getGroup(2));
	stream.setValue(VideoStream::COLORSPACE, matcher.getGroup(3));
	stream.setValue(VideoStream::RESX, matcher.getGroup(4));
	stream.setValue(VideoStream::RESY, matcher.getGroup(5));

	std::string tmp = lineEnd+",";
	RegexTools::Regex reg("([^ ]+)[[:space:]]+([^, ])");
	while(trimBy(",", tmp, first, rest)){
		RegexTools::Matcher m = reg.getMatcher(first);
		if(!m.find()){
			continue;
		}
		if(m.getGroup(2) == "fps"){
			stream.setValue(VideoStream::FPS, matcher.getGroup(1));
		}else if(m.getGroup(2) == "tbr"){
			stream.setValue(VideoStream::TBR, matcher.getGroup(1));
		}else if(m.getGroup(2) == "tbn"){
			stream.setValue(VideoStream::TBN, matcher.getGroup(1));
		}else if(m.getGroup(2) == "tbc"){
			stream.setValue(VideoStream::TBC, matcher.getGroup(1));
		}
		tmp = rest;
	}
	mediaFile.addVideoStream(stream);
}
void InfoLoader::parseAudioStream(const RegexTools::Matcher &matcher){
	std::string first, rest;
	trimBy(".", matcher.getGroup(1), first, rest);
	int f,r;
	strToNumber(first, f);
	strToNumber(rest, r);
	AudioStream stream(f,r);
	stream.setValue(AudioStream::CODEC, matcher.getGroup(2));
	stream.setValue(AudioStream::SAMPLERATE, matcher.getGroup(3));
	stream.setValue(AudioStream::CHANELS, matcher.getGroup(4));
	stream.setValue(AudioStream::BITRATE, matcher.getGroup(6));
	mediaFile.addAudioStream(stream);
}


}
