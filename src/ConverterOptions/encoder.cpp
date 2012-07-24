/*
 * encoder.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "encoder.h"

namespace ConverterOptions {

Encoder::Encoder(){
	this->name = "";
	this->description = "";
	this->bitrate = Bitrates();
}
Encoder::Encoder(std::string name, std::string description, Bitrates bitrate) {
	this->name = name;
	this->description = description;
	this->bitrate = bitrate;

}
std::string Encoder::getEncoderName() const{
	return name;
}
std::string Encoder::getEncoderDescription() const{
	return description;
}
Bitrates Encoder::getBitrates() const{
	return bitrate;
}

void Encoders::addEncoder(const Encoder& encoder){
	encoders[encoder.getEncoderName()] = encoder;
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
