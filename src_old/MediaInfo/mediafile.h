/*
 * mediainfo.h
 *
 *  Created on: 20.6.2012
 *  Author: Martin Geier
 *
 *  Audio and Video information
 */

#ifndef MEDIAINFO_H_
#define MEDIAINFO_H_

#include <vector>
#include <string>
#include "videostream.h"
#include "audiostream.h"
#include <stdexcept>

namespace MediaInfo{

class MediaFile {
public:
	enum State{
		NOT_SET, OK, NOT_FOUND, INVALID_FORMAT
	};
public:
	MediaFile(std::string filePath);
	virtual ~MediaFile();
	std::string getFilePath();

	void setDuration(double duration);
	void setStartTime(double time);
	void setBitrate(const std::string &bitrate);

	void setState(State state);
	State getState();

	double getDuration();
	double getStartTime();
	std::string getBitrate();

	void addVideoStream(VideoStream stream);
	void addAudioStream(AudioStream stream);

	VideoStream getVideoStream(unsigned int index) throw(std::out_of_range);
	int getVideoStreamCaunt();
	AudioStream getAudioStream(int index);
	int getAudioStreamCaunt();

	void setMetadata(std::string key, std::string value);
private:
	double duration;
	double startTime;
	std::string bitrate;
	std::string filePath;
	std::vector<VideoStream> videos;
	std::vector<AudioStream> audios;
	State fileState;
	std::map<std::string, std::string> metadata;
};

}
#endif /* MEDIAINFO_H_ */
