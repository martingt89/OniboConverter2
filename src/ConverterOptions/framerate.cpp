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
	if(framerate > 0){
		return toS(framerate);
	}else{
		return ORIGINAL;
	}
}
Converter::Arguments Framerate::getConvertArguments() const{
	Converter::Arguments args;
	if(framerate > 0){
		Converter::Argument arg("-r");
		arg.addValue(toS(framerate));
		args.push_back(arg);
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
