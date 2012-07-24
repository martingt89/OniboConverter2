/*
 * optionsdatabase.h
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#ifndef OPTIONSDATABASE_H_
#define OPTIONSDATABASE_H_

#include "framerate.h"
#include "samplerate.h"
#include "container.h"
#include "resolution.h"
#include "optionsloader.h"

namespace ConverterOptions {

class OptionsDatabase {
public:
	OptionsDatabase(OptionsLoader* optionsLoader);
	virtual ~OptionsDatabase();
	const Framerates& getFramerates() const;
	const Samplerates& getSamplerates() const;
	const Containers& getContainers() const;
	const Resolutions& getResolutions() const;
private:
	Framerates framerates;
	Samplerates samplerates;
	Containers containers;
	Resolutions resolutions;
};

} /* namespace ConverterOptions */
#endif /* OPTIONSDATABASE_H_ */
