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
#include "channel.h"

namespace ConverterOptions {

class OptionsDatabase {
public:
	OptionsDatabase(OptionsLoader* optionsLoader);
	virtual ~OptionsDatabase();
	const Framerates& getFramerates() const;
	const Samplerates& getSamplerates() const;
	const Containers& getContainers() const;
	const Resolutions& getResolutions() const;
	const Channels& getChannels() const;
	//
	void addUserResolution(const Resolution& resolution);
	void addUserVideoBitrate(const Bitrate& bitrate);
	void addUserAudioBitrate(const Bitrate& bitrate);
	void addUserFFpreset(const FFpreset& ffpreset);
	//
	std::list<Resolution> getUserResolutions() const;
	std::list<Bitrate> getUserVideoBitrate() const;
	std::list<Bitrate> getUserAudioBitrate() const;
	std::list<FFpreset> getUserFFpreset(const std::string& prefix) const;
private:
	const OptionsDatabase& operator=(const OptionsDatabase& database);
	OptionsDatabase(const OptionsDatabase& database);
	Framerates framerates;
	Samplerates samplerates;
	Containers containers;
	Resolutions resolutions;
	Channels channels;

	std::list<Resolution> userResolutions;
	std::list<Bitrate> userVideoBitrate;
	std::list<Bitrate> userAudioBitrate;
	CppExtension::MultiHashMap<std::string, FFpreset> prefixToFFpreset;
};

} /* namespace ConverterOptions */
#endif /* OPTIONSDATABASE_H_ */
