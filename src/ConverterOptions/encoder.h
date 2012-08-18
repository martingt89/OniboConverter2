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

namespace ConverterOptions {

class Encoder {
public:
	enum Type{
		AUDIO, VIDEO, UNSET
	};
public:
	Encoder();
	Encoder(std::string name, std::string type, std::string description, Bitrates bitrate);
	void setFFpresets(const FFpresets& ffpresets, const std::string& prefix);
	bool hasFFpreset();
	std::string getName() const;
	std::string getDescription() const;
	Bitrates getBitrates() const;
	bool getFFPresets(FFpresets& ffpresets);
	std::string getFFPrefix();
	Converter::Arguments getConvertArguments() const;
private:
	std::string name;
	std::string description;
	Bitrates bitrate;
	FFpresets ffpresets;
	bool isSetFFpresets;
	std::string prefix;
	Type encoderType;
};

class Encoders{
public:
	void addEncoder(const Encoder& encoder);
	std::list<Encoder> getEncoders() const;
	Encoder getEncoderByName(const std::string& encoderName) const;
private:
	std::map<std::string, Encoder> encoders;	//todo CppExtension
};

} /* namespace ConverterOptions */
#endif /* ENCODER_H_ */
