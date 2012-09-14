/*
 * audiostream.h
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */

#ifndef AUDIOSTREAM_H_
#define AUDIOSTREAM_H_

#include <string>
#include "stream.h"
#include "../CppExtension/hashmap.h"

namespace MediaFile {

class AudioStream : public Stream{
public:
	enum Audio{
		CODEC, BITRATE, SAMPLERATE, CHANNELS
	};
public:
	AudioStream(int firstNumber, int secondNumber, std::string name = std::string());
	virtual ~AudioStream();
	void setValue(const Audio& name, const std::string& value);
	bool getValue(const Audio& name, std::string& value) const;
private:
	CppExtension::HashMap<Audio, std::string> content;
};

} /* namespace MediaFile */
#endif /* AUDIOSTREAM_H_ */
