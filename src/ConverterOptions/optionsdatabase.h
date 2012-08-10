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
	//
	void addUserResolution(const Resolution& resolution);
	void addUserVideoBitrate(const Bitrate& bitrate);
	void addUserAudioBitrate(const Bitrate& bitrate);
	//
	std::list<Resolution> getUserResolutions() const;
	std::list<Bitrate> getUserVideoBitrate() const;
	std::list<Bitrate> getUserAudioBitrate() const;
private:
	const OptionsDatabase& operator=(const OptionsDatabase& database);
	OptionsDatabase(const OptionsDatabase& database);
	Framerates framerates;
	Samplerates samplerates;
	Containers containers;
	Resolutions resolutions;

	std::list<Resolution> userResolutions;
	std::list<Bitrate> userVideoBitrate;
	std::list<Bitrate> userAudioBitrate;
};

} /* namespace ConverterOptions */
#endif /* OPTIONSDATABASE_H_ */
