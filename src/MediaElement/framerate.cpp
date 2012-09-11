/*
 * framerate.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "framerate.h"
#include "../helper.h"

namespace MediaElement {

static const std::string ORIGINAL="--- original ---";

Framerate::Framerate(double framerate) {
	this->framerate = framerate;
}

double Framerate::getValue() const{
	return framerate;
}
std::string Framerate::readableForm() const{
	if(framerate >= 0){
		return toS(framerate);
	}else{
		return ORIGINAL;
	}
}
bool Framerate::isOriginal() const{
	return framerate < 0;
}
void Framerates::addFramerate(const Framerate& framerate){
	framerates.push_back(framerate);
}

std::list<Framerate> Framerates::getFramerats() const{
	return framerates;
}

} /* namespace MediaElement */
