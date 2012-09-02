/*
 * profil.h
 *
 *  Created on: 29.7.2012
 *      Author: martint
 */

#ifndef PROFILE_H_
#define PROFILE_H_

#include <string>
#include <list>
#include "../CppExtension/hashmap.h"
#include "../ConverterOptions/optionsdatabase.h"

namespace Profile {

class Profile {
public:
	enum Options{
		BEGIN_OPT = 0,
		NAME_OPT = 0,
		CONTAINER_OPT = 1,
		VIDEO_MODE_OPT = 2,
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
		VIDEO_FFPRESET_BUILDIN_OPT = 15,
		//
		AUDIO_MODE_OPT = 16,
		AUDIO_FORMAT_OPT = 17,
		AUDIO_ENCODER_OPT = 18,
		AUDIO_BITRATE_OPT = 19,
		AUDIO_SAMPLERATE_OPT = 20,
		AUDIO_CHANNEL_VALUE_OPT = 21,
		AUDIO_CHANNEL_NAME_OPT = 22,
		//
		END_OPT = 23,
		//
		MANUAL_COMMAND_OPT = 24,
		MANUAL_ARG_OPT = 25,
		UNKNOWN_OPT = 26
	};
	struct ManualSettings{
		std::string command;
		std::list<std::string> args;
	};
public:

	Profile();
	virtual ~Profile();
	void addProperty(const Options& options, const std::string& propertie);
	std::string getProperty(const Options& options) const;
	//
	std::string getName() const;
	bool getContainerName(std::string& containerName) const;
	bool getVideoMode(int& row) const;
	bool getVideoFormatName(std::string& videoFormatName) const;
	bool getVideoEncoderName(std::string& videoEncoderName) const;
	bool getVideoBitrate(ConverterOptions::Bitrate& videoBitrate) const;
	bool getVideoResolution(ConverterOptions::Resolution& resolution, bool& original) const;
	bool getVideoFFpreset(ConverterOptions::FFpreset& ffpreset) const;
	bool getVideoFramerate(ConverterOptions::Framerate& framerate, bool& original) const;
	//
	bool getAudioMode(int& row) const;
	bool getAudioFormatName(std::string& audioFormatName) const;
	bool getAudioEncoderName(std::string& audioEncoderName) const;
	bool getAudioBitrate(ConverterOptions::Bitrate& audioBitrate) const;
	bool getAudioSamplerate(ConverterOptions::Samplerate& audioSamplerate, bool& isOriginal) const;
	bool getAudioChannel(ConverterOptions::Channel& audioChannel, bool& isOriginal) const;
	//
	void getManualSettings(std::list<ManualSettings>& manualSettings) const;
private:
	CppExtension::HashMap<Options, std::string> optionsToValue;
	std::list<ManualSettings> settings;
};

typedef std::list<Profile> Profiles;

} /* namespace Profile */
#endif /* PROFILE_H_ */
