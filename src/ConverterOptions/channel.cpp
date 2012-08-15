/*
 * channel.cpp
 *
 *  Created on: 11.8.2012
 *      Author: martint
 */

#include "channel.h"
#include "../helper.h"

namespace ConverterOptions {

Channel::Channel() {
	name = "";
	value = 0;
}
Channel::Channel(const std::string& name, const int& value){
	this->name = name;
	this->value = value;
}
Channel::~Channel() {

}
int Channel::getValue() const{
	return value;
}
std::string Channel::toStr() const{
	if(name.size() > 0){
		return name;
	}
	return toS(value);
}
} /* namespace ConverterOptions */
