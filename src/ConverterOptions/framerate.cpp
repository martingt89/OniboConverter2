/*
 * framerate.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "framerate.h"
#include "../helper.h"

namespace ConverterOptions {

static const std::string ORIGINAL="--- original ---";

Framerate::Framerate(double framerate) {
	this->framerate = framerate;
}

double Framerate::getValue() const{
	return framerate;
}

std::string Framerate::toStr() const{
	if(framerate >= 0){
		return toS(framerate);
	}else{
		return ORIGINAL;
	}
}
Converter::ConvertSettingsList Framerate::getConvertArguments() const{
	Converter::ConvertSettingsList args;
	if(framerate >= 0){
		Converter::ConvertSettings arg(Converter::ConvertSettings::FRAMERATE);	//-r
		arg.addValue(toS(framerate));
		args.add(arg);
	}
	return args;
}
void Framerates::addFramerate(const Framerate& framerate){
	framerates.push_back(framerate);
}

std::list<Framerate> Framerates::getFramerats() const{
	return framerates;
}

} /* namespace ConverterOptions */
