/*
 * framerate.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "framerate.h"

namespace ConverterOptions {

Framerate::Framerate(double framerate) {
	this->framerate = framerate;
}

double Framerate::getValue() const{
	return framerate;
}

void Framerates::addFramerate(const Framerate& framerate){
	framerates.push_back(framerate);
}

std::list<Framerate> Framerates::getFramerats() const{
	return framerates;
}

} /* namespace ConverterOptions */
