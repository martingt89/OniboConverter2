/*
 * stream.cpp
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */

#include "stream.h"

namespace MediaFile {

Stream::Stream(int firstNumber, int secondNumebr): streamNumber(firstNumber, secondNumebr) {
}

Stream::~Stream() {}

std::pair<int, int> Stream::getStreamNumber() const{
	return streamNumber;
}
} /* namespace MediaFile */
