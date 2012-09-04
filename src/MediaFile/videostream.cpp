/*
 * videostream.cpp
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */

#include "videostream.h"
#include "../helper.h"

namespace MediaFile {

VideoStream::VideoStream(int firstNumber, int secondNumber): Stream(firstNumber,secondNumber){}

void VideoStream::setValue(const Video& name, const std::string& value){
	content.set(name, value);
}

bool VideoStream::getValue(const Video& name, std::string& value) const{
	bool isExistParameter = false;
	value = content.get(name, isExistParameter);
	return isExistParameter;
}

} /* namespace MediaFile */
