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

namespace MediaElement {

class Bitrate {
public:
	Bitrate();
	Bitrate(int bitrate, int minBitrate = -1, int maxBitrate = -1);
	int getValue() const;
	int getMinBitrate() const;
	int getMaxBitrate() const;
	bool operator== (const Bitrate& second) const;
	std::string readableForm() const;

private:
	int value;
	int minBitrate;
	int maxBitrate;
};

typedef std::list<Bitrate> Bitrates;

} /* namespace MediaElement */
#endif /* BITRATE_H_ */
