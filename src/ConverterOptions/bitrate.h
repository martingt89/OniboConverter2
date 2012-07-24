/*
 * bitrate.h
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#ifndef BITRATE_H_
#define BITRATE_H_

#include <list>

namespace ConverterOptions {

class Bitrate {
public:
	Bitrate();
	Bitrate(int bitrate);
	int getValue() const;
private:
	int bitrate;
};

typedef std::list<Bitrate> Bitrates;

} /* namespace ConverterOptions */
#endif /* BITRATE_H_ */
