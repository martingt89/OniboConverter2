/*
 * audiostream.h
 *
 *  Created on: 20.6.2012
 *      Author: martint
 */

#ifndef AUDIOSTREAM_H_
#define AUDIOSTREAM_H_

#include "stream.h"
#include <string>
#include <map>

namespace MediaInfo {

class AudioStream : public Stream{
public:
	AudioStream(int f, int r);
	enum Audio{
			CODEC, BITRATE, SAMPLERATE, CHANELS
	};
	void setValue(Audio name, std::string value);
	std::string getValue(Audio name);
private:
	std::map<Audio, std::string> content;
};

} /* namespace MediaInfo */
#endif /* AUDIOSTREAM_H_ */
