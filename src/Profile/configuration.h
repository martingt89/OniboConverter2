/* ---------------------------------------------------------------------------
** Author: Martin Geier
** configuration.h is part of OniboConverter2.
**
** OniboConverter2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
** -------------------------------------------------------------------------*/

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>
#include <list>
#include "../CppExtension/hashmap.h"
#include "../MediaElement/elementsdb.h"
#include "profile.h"

namespace Profile {

class Configuration {
public:
	enum Options{
		BEGIN_OPT = 0,
		NAME_OPT = 0,
		CONTAINER_OPT = 1,
		VIDEO_MODE_OPT = 2,
		//
		VIDEO_FORMAT_OPT = 3,
		VIDEO_ENCODER_OPT = 4,
		VIDEO_FRAMERATE_OPT = 5,
		VIDEO_BITRATE_OPT = 6,
		VIDEO_BITRATE_MIN_OPT = 7,
		VIDEO_BITRATE_MAX_OPT = 8,
		VIDEO_RESOLUTION_X_OPT = 9,
		VIDEO_RESOLUTION_Y_OPT = 10,
		VIDEO_RESOLUTION_ASP_OPT = 11,
		VIDEO_RESOLUTION_NAME_OPT = 12,
		VIDEO_FFPRESET_PREFIX_OPT = 13,
		VIDEO_FFPRESET_PATH_OPT = 14,
		VIDEO_FFPRESET_TYPE_OPT = 15,
		//
		AUDIO_MODE_OPT = 16,
		AUDIO_FORMAT_OPT = 17,
		AUDIO_ENCODER_OPT = 18,
		AUDIO_GRADE_TYPE_OPT = 19,
		AUDIO_GRADE_VALUE_OPT = 20,
		AUDIO_SAMPLERATE_OPT = 21,
		AUDIO_CHANNEL_VALUE_OPT = 22,
		AUDIO_CHANNEL_NAME_OPT = 23,
		//
		END_OPT = 24,
		//
		MANUAL_COMMAND_OPT = 25,
		MANUAL_ARG_OPT = 26,
		UNKNOWN_OPT = 27
	};
public:
	Configuration() : elementsDb(){};
	Configuration(MediaElement::ElementsDB elementsDb);
	Configuration(const Profile& profile, MediaElement::ElementsDB elementsDb);
	virtual ~Configuration();
	void addProperty(const Options& options, const std::string& propertie);
	std::string getProperty(const Options& options) const;
	void getManualSettings(std::list<Profile::ManualSettings>& manualSettings) const;
	Profile getProfile() const;
private:
	std::string getName() const;
	bool getContainer(MediaElement::Container& container) const;
	bool getVideoMode(int& row) const;
	bool getVideoFormat(MediaElement::Format& videoFormat) const;
	bool getVideoEncoder(MediaElement::Encoder& videoEncoder) const;
	bool getVideoBitrate(MediaElement::Bitrate& videoBitrate) const;
	bool getVideoResolution(MediaElement::Resolution& resolution) const;
	bool getVideoFFpreset(MediaElement::FFpreset& ffpreset) const;
	bool getVideoFramerate(MediaElement::Framerate& framerate) const;
	//
	bool getAudioMode(int& row) const;
	bool getAudioFormat(MediaElement::Format& audioFormat) const;
	bool getAudioEncoder(MediaElement::Encoder& audioEncoder) const;
	bool getAudioGrade(MediaElement::AudioGrade& audioGrade) const;
	bool getAudioSamplerate(MediaElement::Samplerate& audioSamplerate) const;
	bool getAudioChannel(MediaElement::Channel& audioChannel) const;
	//
	CppExtension::HashMap<Options, std::string> optionsToValue;
	std::list<Profile::ManualSettings> settings;
	MediaElement::ElementsDB elementsDb;
};

} /* namespace Profile */
#endif /* CONFIGURATION_H_ */
