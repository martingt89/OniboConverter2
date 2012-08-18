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
	bitrateType = UNSET;
}
Bitrate::Bitrate(int bitrate, std::string type, int minBitrate, int maxBitrate) {
	this->bitrate = bitrate;
	this->minBitrate = minBitrate;
	this->maxBitrate = maxBitrate;
	if(type == "v"){
		bitrateType = VIDEO;
	}else if(type == "a"){
		bitrateType = AUDIO;
	}else{
		bitrateType = UNSET;
	}
}
Bitrate::Bitrate(int bitrate, Type type, int minBitrate, int maxBitrate) {
	this->bitrate = bitrate;
	this->minBitrate = minBitrate;
	this->maxBitrate = maxBitrate;
	bitrateType = type;
}
int Bitrate::getMinBitrate() const{
	return minBitrate;
}
int Bitrate::getMaxBitrate() const{
	return maxBitrate;
}
std::string Bitrate::toStr() const{
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
bool Bitrate::operator== (const Bitrate& second) const{
	return (bitrate == second.bitrate) &&
			(minBitrate == second.minBitrate) &&
			(maxBitrate == second.maxBitrate);
}
Converter::Arguments Bitrate::getConvertArguments() const{
	Converter::Arguments args;
	if(bitrateType == VIDEO){
		Converter::Argument arg("-b");
		arg.addValue(toS(bitrate)+"k");
		args.push_back(arg);
	}
	if(bitrateType == AUDIO){
		Converter::Argument arg("-ab");
		arg.addValue(toS(bitrate)+"k");
		args.push_back(arg);
	}
	return args;
}
} /* namespace ConverterOptions */
