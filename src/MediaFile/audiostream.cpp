/*
 * audiostream.cpp
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */

#include "audiostream.h"
#include <iostream> //todo remove
namespace MediaFile {

AudioStream::AudioStream(int firstNumber, int secondNumber): Stream(firstNumber,secondNumber){

}
AudioStream::~AudioStream(){

}
void AudioStream::setValue(const Audio& name, const std::string& value){
	content.set(name, value);
}

bool AudioStream::getValue(const Audio& name, std::string& value) const{
	bool isExistParameter = false;
	value = content.get(name, isExistParameter);
	return isExistParameter;
}

} /* namespace MediaFile */
