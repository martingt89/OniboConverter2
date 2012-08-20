/*
 * samplerate.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "samplerate.h"
#include "../helper.h"

namespace ConverterOptions {

static const std::string ORIGINAL="--- original ---";

Samplerate::Samplerate(){
	samplerate = 0;
}

Samplerate::Samplerate(int samplerate) {
	this->samplerate = samplerate;
}

int Samplerate::getValue() const{
	return samplerate;
}
std::string Samplerate::toStr() const{
	if(samplerate > 0){
		return toS(samplerate);
	}
	return ORIGINAL;
}
Converter::ConvertSettingsList Samplerate::getConvertArguments() const{
	Converter::ConvertSettingsList args;
	if(samplerate > 0){
		Converter::ConvertSettings arg(Converter::ConvertSettings::SAMPLERATE);		//-ar
		arg.addValue(toS(samplerate));
		args.add(arg);
	}
	return args;
}

void Samplerates::addSamplerate(const Samplerate& samplerate){
	samplerates.push_back(samplerate);
}
std::list<Samplerate> Samplerates::getSamplerates() const{
	return samplerates;
}


} /* namespace ConverterOptions */
