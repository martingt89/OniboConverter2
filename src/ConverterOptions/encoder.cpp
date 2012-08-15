/*
 * encoder.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "encoder.h"
#include "ffpreset.h"

namespace ConverterOptions {

Encoder::Encoder(){
	this->name = "";
	this->description = "";
	this->bitrate = Bitrates();
	isSetFFpresets = false;
}
Encoder::Encoder(std::string name, std::string description, Bitrates bitrate) {
	this->name = name;
	this->description = description;
	this->bitrate = bitrate;
	isSetFFpresets = false;
}
void Encoder::setFFpresets(const FFpresets& ffpresets, const std::string& prefix){
	this->ffpresets = ffpresets;
	isSetFFpresets = true;
	this->prefix = prefix;
}
bool Encoder::hasFFpreset(){
	return isSetFFpresets;
}
std::string Encoder::getFFPrefix(){
	return prefix;
}

std::string Encoder::getName() const{
	return name;
}
std::string Encoder::getDescription() const{
	return description;
}
Bitrates Encoder::getBitrates() const{
	return bitrate;
}
bool Encoder::getFFPresets(FFpresets& ffpresets){
	ffpresets = this->ffpresets;
	return isSetFFpresets;
}
//std::string Encoder::addUserFileWithFFPreset(const std::string &path){
//	if(ffpreset == NULL){
//		//todo assert
//	}
//	return ffpreset->addUserDefineFile(ffpresetPrefix, path);
//}

void Encoders::addEncoder(const Encoder& encoder){
	encoders[encoder.getName()] = encoder;
}
std::list<Encoder> Encoders::getEncoders() const{
	std::list<Encoder> encodersList;
	for(auto iterator = encoders.begin(); iterator != encoders.end(); ++iterator){
		encodersList.push_back(iterator->second);
	}
	return encodersList;
}
Encoder Encoders::getEncoderByName(const std::string& encoderName) const{ //todo encoderName doesn't exist
	auto iterator = encoders.find(encoderName);
	if(iterator != encoders.end()){
		return iterator->second;
	}
	return Encoder();
}

} /* namespace ConverterOptions */
