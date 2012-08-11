/*
 * optionsloader.h
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#ifndef OPTIONSLOADER_H_
#define OPTIONSLOADER_H_

#include "container.h"
#include "framerate.h"
#include "samplerate.h"
#include "resolution.h"
#include "channel.h"

namespace ConverterOptions{

class OptionsLoader{
public:
	virtual ~OptionsLoader(){}
	virtual Containers loadContainers() = 0;
	virtual Framerates loadFramerates() = 0;
	virtual Samplerates loadSamplerates() = 0;
	virtual Resolutions loadResolutions() = 0;
	virtual Channels loadChannels() = 0;
};

}


#endif /* OPTIONSLOADER_H_ */
