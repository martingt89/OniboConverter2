/*
 * encoder.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "encoder.h"
#include "ffpreset.h"
#include "../helper.h"

namespace MediaElement {

Encoder::Encoder(){
	this->name = "";
	this->description = "";
	enableMultithread = false;
}
Encoder::Encoder(std::string name, std::string description, bool isEnableMultithread) {
	this->name = name;
	this->description = description;
	enableMultithread = isEnableMultithread;
}
std::string Encoder::getName() const{
	return name;
}
std::string Encoder::getDescription() const{
	return description;
}
std::string Encoder::readableForm() const{
	return getName();
}
bool Encoder::operator<(const Encoder& second) const{
	return this->name < second.name;
}
bool Encoder::operator==(const Encoder& second) const{
	return this->name == second.name;
}
std::list<std::string> Encoder::getArguments(Encoder::Type encoderType,
		bool enableThreading, int numOfThreads) const{
	std::list<std::string> list;
	if(encoderType == VIDEO){
		list.push_back("-vcodec");
		list.push_back(name);
	}
	if(enableMultithread && enableThreading){
		list.push_back("-threads");
		list.push_back(toS(numOfThreads));
	}
	if(encoderType == AUDIO){
		list.push_back("-acodec");
		list.push_back(name);
	}
	return list;
}
//=======================================================================
void Encoders::addEncoder(const Encoder& encoder){
	encoders.set(encoder.getName(), encoder);
}
std::list<Encoder> Encoders::getEncoders() const{
	return encoders.getListOfValues();
}
Encoder Encoders::getEncoderByName(const std::string& encoderName) const{
	bool isExist = false;
	Encoder enc = encoders.get(encoderName, isExist);
	assert(isExist, "Encoder name doesn't exist: "+encoderName);
	return enc;
}
bool Encoders::getEncoderByName(const std::string& encoderName, Encoder& encoder) const{
	bool isExist = false;
	encoder = encoders.get(encoderName, isExist);
	return isExist;
}

} /* namespace MediaElement */
