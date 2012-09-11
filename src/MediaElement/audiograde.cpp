/*
 * audiograde.cpp
 *
 *  Created on: 11.9.2012
 *      Author: martin
 */

#include "audiograde.h"

#include "../helper.h"

namespace MediaElement {

const static std::string DEFAULT = "-- default --";

AudioGrade::AudioGrade() {
	type = BITRATE_TYPE;
	value = -1;
}

AudioGrade::~AudioGrade() {}

AudioGrade::AudioGrade(int value, Type type){
	this->type = type;
	this->value = value;
}
int AudioGrade::getValue() const{
	return value;
}
bool AudioGrade::operator== (const AudioGrade& second) const{
	return this->value == second.value;
}
std::string AudioGrade::readableForm() const{
	if(this->isDefault()){
		return DEFAULT;
	}
	return toS(value);
}
AudioGrade::Type AudioGrade::getType() const{
	return type;
}

bool AudioGrade::isDefault() const{
	return value < 0;
}

} /* namespace MediaElement */
