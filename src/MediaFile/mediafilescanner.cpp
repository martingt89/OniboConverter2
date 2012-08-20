/*
 * mediafilescanner.cpp
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */

#include "mediafilescanner.h"

#include "../helper.h"
#include <iostream> //todo remove
namespace MediaFile {

MediaFileScanner::MediaFileScanner(Path filePath) :
		durationRegex("Duration: ([\\.:[:digit:]]+), start: ([\\.[:digit:]]+), bitrate: (.*)"),
		videoStreamRegex("Stream #(.+): Video: ([^,]+), ([^,]+), ([[:digit:]]+)x([[:digit:]]+)[^,]*,"),
		audioStreamRegex("Stream #(.+): Audio: ([^,]+), ([[:digit:]]+) Hz, ([^,]+), ([^,]+), ([^,]+)"),
		metadataRegex("^[[:space:]]{4}([^[:space:]]+)[^:]*:[[:space:]]*(.+)$"), filePath(filePath) {

	bitrate = "";
	duration = -1;
	parseState = State::START;

	//std::string path = Settings::getSettings()->getValue(Settings::FFPATH); TODO get ffmpeg

	std::string ffmpegPath = "ffmpeg";

	std::list<std::string> args;

	args.push_back("-i");
	args.push_back(filePath.getPath());

	ProcessExecutor::Process process(ffmpegPath, args);

	if (process.waitForProcessBegin() != 0) {
		std::string messages;
		while (process.getLog() >> messages) {
			std::cout << "Process::Executor error: " << messages << std::endl;	//todo logging
		}
		//todo excetion
		return;
	}
	std::string line;
	while (process.getStdErr() >> line) {
		parseLine(line);
	}
}

MediaFileScanner::~MediaFileScanner() {}

double MediaFileScanner::getStartTime(){
	return startPosition;
}
double MediaFileScanner::getDuration(){
	return duration;
}
std::string MediaFileScanner::getBitrate(){
	//std::cout<<"bitrate: "<<bitrate<<std::endl;
	return bitrate;
}
std::list<VideoStream> MediaFileScanner::getVideoStreams(){
	return videoStreams;
}
std::list<AudioStream> MediaFileScanner::getAudioStreams(){
	return audioStreams;
}
MediaFileScanner::ScanResult MediaFileScanner::getFinalStatus(){
	switch(parseState){
		case State::END: return  ScanResult::OK_RESULT;
		case State::FILE_NOT_FOUND: return  ScanResult::FILE_NOT_FOUND_RESULT;
		case State::INVALID_DATA: return  ScanResult::INVALID_DATA_RESULT;
		default: return  ScanResult::OTHER_RESULT;
	}
}
void MediaFileScanner::parseLine(const std::string &line){
	if(parseState == START){
		if(line.find("Metadata:")){
			parseState = METADATA;
			return;
		}
	}else if(parseState == METADATA){
		RegexTools::Matcher m = metadataRegex.getMatcher(line);
		if(m.find()){
			metadata.push_back(std::make_pair(m.getGroup(1), m.getGroup(2)));
		}
	}
	if(parseState == START || parseState == METADATA){
		RegexTools::Matcher m = durationRegex.getMatcher(line);
		if(m.find()){
			parseState = DURATION;
			parseDuration(m);
		}else if(line.find(filePath.getPath()+": Invalid data found") == 0){
			parseState = INVALID_DATA;
		}else if(line.find(filePath.getPath()+": No such file or directory") == 0){
			parseState = FILE_NOT_FOUND;
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
		}
	}
}

void MediaFileScanner::parseDuration(const RegexTools::Matcher &matcher){	//magic, don't touch this
	bitrate = matcher.getGroup(3);

	startPosition = toN(matcher.getGroup(2), double());

	std::string tmp = matcher.getGroup(1)+":";
	std::string first;
	std::string rest;
	double number;
	duration = 0;
	while(trimBy(":", tmp, first, rest)){
		duration *= 60;
		number = toN(first, double());
		duration += number;
		tmp = rest;
	}
}

void MediaFileScanner::parseVideoStream(const RegexTools::Matcher &matcher, const std::string& lineEnd){
	std::string first, rest;
	trimBy(".", matcher.getGroup(1), first, rest);
	int firstNumber = toN(first, int());
	int secondNumber = toN(rest, int());

	VideoStream stream(firstNumber,secondNumber);
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
	videoStreams.push_back(stream);
}
void MediaFileScanner::parseAudioStream(const RegexTools::Matcher &matcher){
	std::string first, rest;
	trimBy(".", matcher.getGroup(1), first, rest);
	int firstNumber = toN(first, int());
	int secondNumber = toN(rest, int());

	AudioStream stream(firstNumber,secondNumber);
	stream.setValue(AudioStream::CODEC, matcher.getGroup(2));
	stream.setValue(AudioStream::SAMPLERATE, matcher.getGroup(3));
	stream.setValue(AudioStream::CHANNELS, matcher.getGroup(4));
	stream.setValue(AudioStream::BITRATE, matcher.getGroup(6));
	audioStreams.push_back(stream);
}

bool MediaFileScanner::trimBy(const std::string& delimiter, const std::string& input, std::string& first,
		std::string& rest) {
	std::string::size_type pos = input.find(delimiter);
	if (pos == std::string::npos) {
		return false;
	}
	first = input.substr(0, pos);
	rest = input.substr(pos + delimiter.size());
	return true;
}

} /* namespace MediaFile */
