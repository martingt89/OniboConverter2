/*
 * encoder.cpp
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#include "encoder.h"

namespace AVBox {

Encoder::Encoder(const std::string& encoder, const std::string& description) {
	this->encoder = encoder;
	this->description = description;
}
Encoder::Encoder(const Encoder& old, const std::string& description){
	encoder = old.encoder;
	this->description = description;
	this->options = old.options;
}
Encoder::Encoder(const std::string& encoder){
	this->encoder = encoder;
	this->description = "";
}
Encoder::Encoder(){
	this->encoder = "";
	this->description = "";
}
Encoder::~Encoder() {}

void Encoder::addOptions(std::string name, std::string value){
	if(value.size() > 0)
		options[name] = value;
}

std::string Encoder::getEncoder() const{
	return encoder;
}
std::string Encoder::getDescription() const{
	return description;
}
std::map<std::string, std::string> Encoder::getOptions() const{
	return options;
}
} /* namespace AVBox */
