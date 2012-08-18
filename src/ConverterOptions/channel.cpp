/*
 * channel.cpp
 *
 *  Created on: 11.8.2012
 *      Author: martint
 */

#include "channel.h"
#include "../helper.h"

namespace ConverterOptions {
static const std::string ORIGINAL="--- original ---";
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
	if(value <= 0){
		return ORIGINAL;
	}
	if(name.size() > 0){
		return name;
	}
	return toS(value);
}
Converter::Arguments Channel::getConvertArguments() const{
	Converter::Arguments args;
	if(value > 0){
		Converter::Argument arg("-ac");
		arg.addValue(toS(value));
		args.push_back(arg);
	}
	return args;
}
} /* namespace ConverterOptions */
