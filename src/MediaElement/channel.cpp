/*
 * channel.cpp
 *
 *  Created on: 11.8.2012
 *      Author: martint
 */

#include "channel.h"
#include "../helper.h"

namespace MediaElement {

static const std::string ORIGINAL="--- original ---";

Channel::Channel() {
	name = "";
	value = -1;
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
//std::string Channel::toStr() const{
//	if(value < 0){
//		return ORIGINAL;
//	}
//	if(name.size() >= 0){
//		return name;
//	}
//	return toS(value);
//}
std::string Channel::readableForm() const{
	if(value < 0){
		return ORIGINAL;
	}
	if(name.size() >= 0){
		return name;
	}
	return toS(value);
}
//Converter::ConvertSettingsList Channel::getConvertArguments() const{
//	Converter::ConvertSettingsList args;
//	if(value >= 0){
//		Converter::ConvertSettings arg(Converter::ConvertSettings::CHANNELS);		//-ac
//		arg.addValue(toS(value));
//		args.add(arg);
//	}
//	return args;
//}
std::string Channel::getName() const{
	return name;
}
bool Channel::isOriginal() const{
	return value < 0;
}
} /* namespace MediaElement */
