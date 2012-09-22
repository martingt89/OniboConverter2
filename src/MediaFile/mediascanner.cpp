/* ---------------------------------------------------------------------------
** Author: Martin Geier
** mediascanner.cpp is part of OniboConverter2.
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

#include "mediascanner.h"

#include "../helper.h"
#include "../userpreferences.h"
#include <iostream> //todo remove
namespace MediaFile {

static const std::string DEFAULT_STREAM = "(default)";

MediaScanner::MediaScanner(Path filePath) :
		durationRegex("Duration: ([\\.:[:digit:]]+|N/A), start: ([\\.[:digit:]]+), bitrate: (.*)"),
		videoStreamRegex("Stream #(([0-9]+)[.:]([0-9]+))(.*): Video: ([^,]+), ([^,]+), ([[:digit:]]+)x([[:digit:]]+)[^,]*,(.*)$"),
		audioStreamRegex("Stream #(([0-9]+)[.:]([0-9]+))(.*): Audio: ([^,]+), ([[:digit:]]+) Hz(.*)$"),
		metadataRegex("^[[:space:]]{4}([^[:space:]]+)[^:]*:[[:space:]]*(.+)$"), filePath(filePath) {

	bitrate = "";
	duration = -1;
	parseState = State::START;

	Path externalConverter = UserPreferences::getInstance()->getExtConverterPath();

	std::list<std::string> args;

	args.push_back("-i");
	args.push_back(filePath.getPath());

	ProcessExecutor::Process process(externalConverter.getPath(), args);

	if (process.waitForProcessBegin() != 0) {
		std::string messages;
		while (process.getLog() >> messages) {
			std::cerr << "Process::Executor error: " << messages << std::endl;	//todo logging
		}
		//todo excetion
		return;
	}
	std::string line;
	while (process.getStdErr() >> line) {
		parseLine(line);
	}
}

MediaScanner::~MediaScanner() {}

double MediaScanner::getStartTime(){
	return startPosition;
}
double MediaScanner::getDuration(){
	return duration;
}
std::string MediaScanner::getBitrate(){
	return bitrate;
}
std::list<VideoStream> MediaScanner::getVideoStreams(){
	return videoStreams;
}
std::list<AudioStream> MediaScanner::getAudioStreams(){
	return audioStreams;
}
MediaScanner::ScanResult MediaScanner::getFinalStatus(){
	switch(parseState){
		case State::END: return  ScanResult::OK_RESULT;
		case State::FILE_NOT_FOUND: return  ScanResult::FILE_NOT_FOUND_RESULT;
		case State::INVALID_DATA: return  ScanResult::INVALID_DATA_RESULT;
		default: return  ScanResult::OTHER_RESULT;
	}
}
void MediaScanner::parseLine(const std::string &line){
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
			parseVideoStream(videoMatcher, line);
		}else if(audioMatcher.find()){
			parseAudioStream(audioMatcher, line);
		}else if(line == "At least one output file must be specified"){
			parseState = State::END;
		}
	}
}

void MediaScanner::parseDuration(const RegexTools::Matcher &matcher){	//magic, don't touch this
	matcher.getGroup(3, bitrate);
	std::string startPosStr = "";
	matcher.getGroup(2, startPosStr);
	startPosition = toN(startPosStr, double());

	std::string tmp = "";
	matcher.getGroup(1, tmp);
	if(tmp != "N/A"){
		tmp += ":";
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
	}else{
		duration = -1;
	}
}

void MediaScanner::parseVideoStream(const RegexTools::Matcher &matcher, const std::string& line){
	int firstNumber = toN(matcher.getGroup(2), int());
	int secondNumber = toN(matcher.getGroup(3), int());
	std::string id = matcher.getGroup(1);
	std::string streamLanguage =  matcher.getGroup(4);

	VideoStream stream(firstNumber,secondNumber, id, streamLanguage);
	stream.setValue(VideoStream::CODEC, matcher.getGroup(5));
	stream.setValue(VideoStream::COLORSPACE, matcher.getGroup(6));
	stream.setValue(VideoStream::RESX, matcher.getGroup(7));
	stream.setValue(VideoStream::RESY, matcher.getGroup(8));

	std::string tmp = matcher.getGroup(9)+",";
	std::string first, rest;
	RegexTools::Regex reg("([^ ]+)[[:space:]]+([^, ]+)");
	while(trimBy(",", tmp, first, rest)){
		RegexTools::Matcher m = reg.getMatcher(first);
		if(!m.find()){
			tmp = rest;
			continue;
		}
		if(m.getGroup(2) == "fps"){
			stream.setValue(VideoStream::FPS, m.getGroup(1));
		}else if(m.getGroup(2) == "tbr"){
			stream.setValue(VideoStream::TBR, m.getGroup(1));
		}else if(m.getGroup(2) == "tbn"){
			stream.setValue(VideoStream::TBN, m.getGroup(1));
		}else if(m.getGroup(2) == "tbc"){
			stream.setValue(VideoStream::TBC, m.getGroup(1));
		}
		tmp = rest;
	}

	if(line.find(DEFAULT_STREAM) == (line.size() - DEFAULT_STREAM.size())){
		stream.setDefault(true);
	}else{
		stream.setDefault(false);
	}
	videoStreams.push_back(stream);
}
void MediaScanner::parseAudioStream(const RegexTools::Matcher &matcher, const std::string& line){
	int firstNumber = toN(matcher.getGroup(2), int());
	int secondNumber = toN(matcher.getGroup(3), int());
	std::string id = matcher.getGroup(1);
	std::string streamName = matcher.getGroup(4);

	AudioStream stream(firstNumber,secondNumber, id, streamName);
	stream.setValue(AudioStream::CODEC, matcher.getGroup(5));
	stream.setValue(AudioStream::SAMPLERATE, matcher.getGroup(6));
	std::string endLine = matcher.getGroup(7);

	std::string tmp = endLine.substr(1) + ",";
	int i = 0;
	std::string first, rest;
	stream.setValue(AudioStream::BITRATE, "N/A");
	while(trimBy(",", tmp, first, rest)){
		if(i == 0){
			stream.setValue(AudioStream::CHANNELS, clearString(first));
		}
		if(i == 2){
			stream.setValue(AudioStream::BITRATE, clearString(first));
		}
		++i;
		tmp = rest;
	}
	if(line.find(DEFAULT_STREAM) == (line.size() - DEFAULT_STREAM.size())){
		stream.setDefault(true);
	}else{
		stream.setDefault(false);
	}
	audioStreams.push_back(stream);
}

bool MediaScanner::trimBy(const std::string& delimiter, const std::string& input, std::string& first,
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
