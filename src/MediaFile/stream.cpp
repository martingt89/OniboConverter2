/*
 * stream.cpp
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */

#include "stream.h"

namespace MediaFile {

Stream::Stream(int firstNumber, int secondNumebr, std::string name) :
		streamNumber(firstNumber, secondNumebr), name(name) {
}

Stream::~Stream() {}

std::pair<int, int> Stream::getStreamNumber() const{
	return streamNumber;
}
std::string Stream::getStreamName() const{
	return name;
}
} /* namespace MediaFile */
