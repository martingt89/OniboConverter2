/* ---------------------------------------------------------------------------
** Author: Martin Geier
** mediascanner.h is part of OniboConverter2.
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
	void parseVideoStream(const RegexTools::Matcher &m, const std::string& line);
	void parseAudioStream(const RegexTools::Matcher &matcher, const std::string& line);

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
