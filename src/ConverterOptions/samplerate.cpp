/*
 * samplerate.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "samplerate.h"
#include "../helper.h"

namespace ConverterOptions {

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
	return toS(samplerate);
}
void Samplerates::addSamplerate(const Samplerate& samplerate){
	samplerates.push_back(samplerate);
}
std::list<Samplerate> Samplerates::getSamplerates() const{
	return samplerates;
}


} /* namespace ConverterOptions */
