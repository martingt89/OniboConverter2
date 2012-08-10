/*
 * bitrate.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "bitrate.h"
#include "../helper.h"

namespace ConverterOptions {

Bitrate::Bitrate(){
	this->bitrate = 0;
	minBitrate = -1;
	maxBitrate = -1;
}
Bitrate::Bitrate(int bitrate, int minBitrate, int maxBitrate) {
	this->bitrate = bitrate;
	this->minBitrate = minBitrate;
	this->maxBitrate = maxBitrate;
}

int Bitrate::getMinBitrate() const{
	return minBitrate;
}
int Bitrate::getMaxBitrate() const{
	return maxBitrate;
}
Bitrate::operator std::string() const{
	std::string min = " ";
	if(minBitrate > 0){
		min = " "+toS(minBitrate);
	}
	std::string max = " ";
	if(maxBitrate > 0){
		max = " "+toS(maxBitrate);
	}
	return toS(bitrate) + min + max;
}

int Bitrate::getValue() const{
	return bitrate;
}

} /* namespace ConverterOptions */
