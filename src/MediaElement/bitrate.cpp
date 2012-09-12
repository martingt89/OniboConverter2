/*
 * bitrate.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "bitrate.h"
#include "../helper.h"

namespace MediaElement {

Bitrate::Bitrate(){
	this->value = 0;
	minBitrate = -1;
	maxBitrate = -1;
}
Bitrate::Bitrate(int bitrate, int minBitrate, int maxBitrate) {
	this->value = bitrate;
	this->minBitrate = minBitrate;
	this->maxBitrate = maxBitrate;
}
int Bitrate::getMinBitrate() const{
	return minBitrate;
}
int Bitrate::getMaxBitrate() const{
	return maxBitrate;
}
std::string Bitrate::readableForm() const{
	std::string min = " -";
	if(minBitrate >= 0){
		min = " "+toS(minBitrate);
	}
	std::string max = " -";
	if(maxBitrate >= 0){
		max = " "+toS(maxBitrate);
	}
	if(maxBitrate >= 0 || minBitrate >= 0){
		return toS(value) + min + max;
	}
	return toS(value);
}
int Bitrate::getValue() const{
	return value;
}
bool Bitrate::operator== (const Bitrate& second) const{
	return (value == second.value) &&
			(minBitrate == second.minBitrate) &&
			(maxBitrate == second.maxBitrate);
}
} /* namespace MediaElement */
