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

namespace ConverterOptions {

class Bitrate {
public:
	Bitrate();
	Bitrate(int bitrate, int minBitrate = -1, int maxBitrate = -1);
	int getValue() const;
	int getMinBitrate() const;
	int getMaxBitrate() const;
	operator std::string() const;
private:
	int bitrate;
	int minBitrate;
	int maxBitrate;
};

typedef std::list<Bitrate> Bitrates;

} /* namespace ConverterOptions */
#endif /* BITRATE_H_ */
