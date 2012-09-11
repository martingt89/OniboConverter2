/*
 * samplerate.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "samplerate.h"
#include "../helper.h"

namespace MediaElement {

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
std::string Samplerate::readableForm() const{
	if(samplerate >= 0){
		return toS(samplerate);
	}
	return ORIGINAL;
}
bool Samplerate::isOriginal() const{
	return samplerate < 0;
}
//=================================================================================================
void Samplerates::addSamplerate(const Samplerate& samplerate){
	samplerates.push_back(samplerate);
}
std::list<Samplerate> Samplerates::getSamplerates() const{
	return samplerates;
}


} /* namespace MediaElement */
