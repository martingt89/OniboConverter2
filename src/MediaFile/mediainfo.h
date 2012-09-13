/*
 * mediainfo.h
 *
 *  Created on: 13.9.2012
 *      Author: martin
 */

#ifndef MEDIAINFO_H_
#define MEDIAINFO_H_

#include "../CppExtension/path.h"
#include "videostream.h"
#include "audiostream.h"
#include <string>
#include <vector>


namespace MediaFile {

class MediaInfo {
public:
	enum ScanStatus{
		NOSCAN, OK, INVALID
	};
	MediaInfo(const Path& mediaPath);
	virtual ~MediaInfo();
	ScanStatus scanMediaFile();

	double getDuration() const;
	double getStartTime() const;
	std::string getBitrate() const;
	std::vector<VideoStream> getVideoStreams() const;
	std::vector<AudioStream> getAudioStreams() const;
	ScanStatus getScanStatus() const;
private:
	Path mediaPath;
	ScanStatus scanStatus;
	double duration;
	double startTime;
	std::string bitrate;
	std::vector<VideoStream> videos;
	std::vector<AudioStream> audios;
};

} /* namespace MediaFile */
#endif /* MEDIAINFO_H_ */
