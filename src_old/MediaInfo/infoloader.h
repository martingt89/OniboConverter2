/*
 * infoloader.h
 *
 *  Created on: 26.6.2012
 *      Author: martint
 */

#ifndef INFOLOADER_H_
#define INFOLOADER_H_

#include <string>
#include "mediafile.h"
#include "../Tools/regextools.h"

namespace MediaInfo{

class InfoLoader {
public:
	InfoLoader(std::string file);
	virtual ~InfoLoader();
	MediaInfo::MediaFile getMediaInfo();
private:
	enum State{
		START, METADATA, DURATION, END, INVALID_DATA, FILE_NOT_FOUND
	};
	std::string file;
	void parse(const std::string &line);
	void parseDuration(const RegexTools::Matcher &matcher);
	void parseVideoStream(const RegexTools::Matcher &m, const std::string& lineEnd);
	void parseAudioStream(const RegexTools::Matcher &matcher);
	State parseState;
	RegexTools::Regex durationRegex;
	RegexTools::Regex videoStreamRegex;
	RegexTools::Regex audioStreamRegex;
	RegexTools::Regex metadataRegex;
	MediaInfo::MediaFile mediaFile;
};

}

#endif /* INFOLOADER_H_ */
