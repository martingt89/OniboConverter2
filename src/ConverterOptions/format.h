/*
 * format.h
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#ifndef FORMAT_H_
#define FORMAT_H_

#include "encoder.h"

namespace ConverterOptions {

class Format {
public:
	enum FormatType{
		FORMAT_TYPE_AUDIO, FORMAT_TYPE_VIDEO
	};
public:
	Format();
	Format(std::string name, FormatType formatType, Encoders encoders);
	std::string getName() const;
	FormatType getFormatType() const;
	Encoders getEncoders() const;
private:
	std::string name;
	FormatType formatType;
	Encoders encoders;
};

class Formats{
public:
	void addFormat(const Format& format);
	std::list<Format> getVideoFormatsList() const;
	std::list<Format> getAudioFormatsList() const;
	Format getFormatByName(std::string formatName) const;
	bool isAudioOnly() const;
private:
	std::map<std::string, Format> videoFormats;
	std::map<std::string, Format> audioFormats;
};

} /* namespace ConverterOptions */
#endif /* FORMAT_H_ */
