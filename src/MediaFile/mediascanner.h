/*
 * mediascanner.h
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */

#ifndef MEDIASCANNER_H_
#define MEDIASCANNER_H_

#include <string>
#include <list>
#include "../CppExtension/path.h"
#include "../RegexTools/regextools.h"
#include "../ProcessExecutor/process.h"
#include "audiostream.h"
#include "videostream.h"

namespace MediaFile {

class MediaScanner {
private:
	enum State{
		START, METADATA, DURATION, END, INVALID_DATA, FILE_NOT_FOUND
	};
public:
	enum ScanResult{
		OK_RESULT, INVALID_DATA_RESULT, FILE_NOT_FOUND_RESULT, OTHER_RESULT
	};
public:
	MediaScanner(Path filePath);
	virtual ~MediaScanner();
	double getStartTime();
	double getDuration();
	std::string getBitrate();
	std::list<VideoStream> getVideoStreams();
	std::list<AudioStream> getAudioStreams();
	ScanResult getFinalStatus();
private:
	bool trimBy(const std::string& delimiter, const std::string& input, std::string& first,
			std::string& rest);
	void parseLine(const std::string &line);
	void parseDuration(const RegexTools::Matcher &matcher);
	void parseVideoStream(const RegexTools::Matcher &m);
	void parseAudioStream(const RegexTools::Matcher &matcher);

	RegexTools::Regex durationRegex;
	RegexTools::Regex videoStreamRegex;
	RegexTools::Regex audioStreamRegex;
	RegexTools::Regex metadataRegex;
	Path filePath;
	State parseState;

	std::list<std::pair<std::string, std::string> > metadata;
	std::string bitrate;
	double startPosition;
	double duration;
	std::list<AudioStream> audioStreams;
	std::list<VideoStream> videoStreams;
};

} /* namespace MediaFile */
#endif /* MEDIASCANNER_H_ */
