/*
 * optionsdatabase.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "optionsdatabase.h"

namespace ConverterOptions {

OptionsDatabase::OptionsDatabase(OptionsLoader* optionsLoader) {
	framerates = optionsLoader->loadFramerates();
	samplerates = optionsLoader->loadSamplerates();
	containers = optionsLoader->loadContainers();
	resolutions = optionsLoader->loadResolutions();
}

OptionsDatabase::~OptionsDatabase() {
	// TODO Auto-generated destructor stub
}

const Framerates& OptionsDatabase::getFramerates() const{
	return framerates;
}
const Samplerates& OptionsDatabase::getSamplerates() const{
	return samplerates;
}
const Containers& OptionsDatabase::getContainers() const{
	return containers;
}
const Resolutions& OptionsDatabase::getResolutions() const{
	return resolutions;
}

} /* namespace ConverterOptions */
