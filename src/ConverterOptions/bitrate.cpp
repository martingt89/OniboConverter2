/*
 * bitrate.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "bitrate.h"

namespace ConverterOptions {

Bitrate::Bitrate(){
	this->bitrate = 0;
}
Bitrate::Bitrate(int bitrate) {
	this->bitrate = bitrate;
}

int Bitrate::getValue() const{
	return bitrate;
}

} /* namespace ConverterOptions */
