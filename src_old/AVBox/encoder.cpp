/*
 * encoder.cpp
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#include "encoder.h"

namespace AVBox {

Encoder::Encoder(const std::string& encoder, const std::string& description, const Type& type) {
	this->encoder = encoder;
	this->description = description;
	this->type = type;
}

Encoder::Encoder(){
	this->encoder = "";
	this->description = "";
	type = UNKNOWN;
}
Encoder::~Encoder() {}

void Encoder::addOptions(std::string name, std::string value){
	if(value.size() > 0)
		options[name] = value;
}

std::string Encoder::getName() const{
	return encoder;
}
std::string Encoder::getDescription() const{
	return description;
}
std::map<std::string, std::string> Encoder::getOptions() const{
	return options;
}
bool Encoder::getOptions(const std::string& name, std::string& returnValue) const{
	std::map<std::string, std::string>::const_iterator it;
	it = options.find(name);
	if(it != options.end()){
		returnValue = it->second;
		return true;
	}
	return false;
}
} /* namespace AVBox */
