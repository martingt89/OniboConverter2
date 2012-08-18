/*
 * bitrate.h
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#ifndef BITRATE_H_
#define BITRATE_H_

#include <list>
#include <string>
#include "../Converter/argument.h"

namespace ConverterOptions {

class Bitrate {
public:
	enum Type{
		VIDEO, AUDIO, UNSET
	};
public:
	Bitrate();
	Bitrate(int bitrate, std::string type, int minBitrate = -1, int maxBitrate = -1);
	Bitrate(int bitrate, Type type, int minBitrate = -1, int maxBitrate = -1);
	int getValue() const;
	int getMinBitrate() const;
	int getMaxBitrate() const;
	bool operator== (const Bitrate& second) const;
	std::string toStr() const;
	Converter::Arguments getConvertArguments() const;
private:
	int bitrate;
	int minBitrate;
	int maxBitrate;
	Type bitrateType;
};

typedef std::list<Bitrate> Bitrates;

} /* namespace ConverterOptions */
#endif /* BITRATE_H_ */
