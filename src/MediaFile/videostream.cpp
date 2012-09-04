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

void VideoStream::setValue(Video name, std::string value){
	content.set(name, value);
}

std::string VideoStream::getValue(Video name){
	bool isExistParameter = false;
	std::string value = content.get(name, isExistParameter);
	assert(!isExistParameter, "Video stream name doesn't exist");
	return value;
}

} /* namespace MediaFile */
