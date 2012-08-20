/*
 * mediafile.h
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */

#ifndef MEDIAFILE_H_
#define MEDIAFILE_H_

#include <string>
#include <vector>
#include <stdexcept>
#include "../CppExtension/path.h"
//#include "../CppExtension/hashmap.h"
#include "videostream.h"
#include "audiostream.h"

namespace MediaFile {

class MediaFile {
public:
	enum State{
		NOT_SET, OK, NOT_FOUND, INVALID_FORMAT
	};
public:
	MediaFile(Path filePath);
	virtual ~MediaFile();

	bool scanMediaFile();
	bool isSet();
	bool isValid();

//	std::string getFilePath();

//	void setDuration(double duration);
//	void setStartTime(double time);
//	void setBitrate(const std::string &bitrate);

//	void setState(State state);
	State getState();

	double getDuration();
	double getStartTime();
	std::string getBitrate();

//	void addVideoStream(VideoStream stream);
//	void addAudioStream(AudioStream stream);

	VideoStream getVideoStream(unsigned int index) throw(std::out_of_range);
	int getNumberOfVideoStreams();
	AudioStream getAudioStream(int index);
	int getNumberOfAudioStreams();

//	void setMetadata(std::string key, std::string value);
private:
	Path filePath;
	double duration;
	double startTime;
	State fileState;
	std::string bitrate;
	std::vector<VideoStream> videos;
	std::vector<AudioStream> audios;
	bool set;
	bool valid;
//	CppExtension::HashMap<std::string, std::string> metadata;
};

} /* namespace MediaFile */
#endif /* MEDIAFILE_H_ */
