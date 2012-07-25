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

namespace ConverterOptions {

class Encoder {
public:
	Encoder();
	Encoder(std::string name, std::string description, Bitrates bitrate);
	void setFFreset(const std::string& ffpreset);
	std::string getName() const;
	std::string getDescription() const;
	Bitrates getBitrates() const;
private:
	std::string name;
	std::string description;
	Bitrates bitrate;
	bool hasFFpreset;
	std::string ffpreset;
};

class Encoders{
public:
	void addEncoder(const Encoder& encoder);
	std::list<Encoder> getEncoders() const;
	Encoder getEncoderByName(const std::string& encoderName) const;
private:
	std::map<std::string, Encoder> encoders;
};

} /* namespace ConverterOptions */
#endif /* ENCODER_H_ */
