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
	encoderType = UNSET;
	enableMultithread = false;
}
Encoder::Encoder(std::string name, std::string type, std::string description, Bitrates bitrate,
		bool isEnableMultithread) {
	this->name = name;
	this->description = description;
	this->bitrate = bitrate;
	isSetFFpresets = false;
	enableMultithread = isEnableMultithread;
	encoderType = UNSET;
	if(type == "v"){
		encoderType = VIDEO;
	}else if(type == "a"){
		encoderType = AUDIO;
	}
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
Converter::ConvertSettingsList Encoder::getConvertArguments() const{
	Converter::ConvertSettingsList args;
	if(encoderType == VIDEO){
		Converter::ConvertSettings arg(Converter::ConvertSettings::VCODEC);	//-vcodec
		arg.addValue(name);
		args.add(arg);
	}
	if(enableMultithread){
		Converter::ConvertSettings arg(Converter::ConvertSettings::MULTITHREAD);
		args.add(arg);
	}
	if(encoderType == AUDIO){
		Converter::ConvertSettings arg(Converter::ConvertSettings::ACODEC);	//-acodec
		arg.addValue(name);
		args.add(arg);
	}
	return args;
}
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
