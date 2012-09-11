/*
 * encoder.h
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <string>
#include <map>
#include "bitrate.h"
#include "ffpreset.h"
#include "../CppExtension/hashmap.h"

namespace MediaElement {

class Encoder {
public:
	enum Type{
		AUDIO, VIDEO
	};
public:
	Encoder();
	Encoder(std::string name, std::string description, bool isEnableMultithread = false);

	std::string getName() const;
	std::string getDescription() const;
	std::string readableForm() const;
	bool operator<(const Encoder& second) const;
	bool operator==(const Encoder& second) const;
	std::list<std::string> getArguments(Encoder::Type encoderType,
			bool enableThreading, int numOfThreads) const;
private:
	std::string name;
	std::string description;
	bool enableMultithread;
};

class Encoders{
public:
	void addEncoder(const Encoder& encoder);
	std::list<Encoder> getEncoders() const;
	Encoder getEncoderByName(const std::string& encoderName) const;
	bool getEncoderByName(const std::string& encoderName, Encoder& encoder) const;
private:
	CppExtension::HashMap<std::string, Encoder> encoders;
};

} /* namespace MediaElement */
#endif /* ENCODER_H_ */
