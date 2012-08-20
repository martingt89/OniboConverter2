/*
 * audiostream.cpp
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */

#include "audiostream.h"

namespace MediaFile {

AudioStream::AudioStream(int firstNumber, int secondNumber): Stream(firstNumber,secondNumber){

}
AudioStream::~AudioStream(){

}
void AudioStream::setValue(Audio name, std::string value){
	content.set(name, value);
}

std::string AudioStream::getValue(Audio name){
	bool isExistParameter = false;
	std::string value = content.get(name, isExistParameter);
	if(!isExistParameter){
		//todo log
	}
	return value;
}

} /* namespace MediaFile */
