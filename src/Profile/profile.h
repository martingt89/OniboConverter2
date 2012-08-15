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
		VIDEO_FFPRESET_OPT = 13,

		END_OPT = 14
	};
public:
	Profile();
	virtual ~Profile();
	void addProperty(const Options& options, const std::string& propertie);
	//
	std::string getName() const;
//	std::string getProperty(const Options& options) const;
//	std::string getProperty(const Options& options, bool& exist) const;
	bool getContainerName(std::string& containerName) const;
	bool getVideoMode(int& row) const;
	bool getVideoFormatName(std::string& videoFormatName) const;
	bool getVideoEncoderName(std::string& videoEncoderName) const;
	bool getVideoBitrate(ConverterOptions::Bitrate& videoBitrate) const;
	bool getVideoResolution(ConverterOptions::Resolution& resolution, bool& original) const;
	//bool getFFpreset(ConverterOptions::FFpreset&)
	bool getVideoFramerate(ConverterOptions::Framerate& framerate, bool& original) const;
	//
	bool getAudioMode(int& row) const;



private:
	CppExtension::HashMap<Options, std::string> optionsToValue;
};

typedef std::list<Profile> Profiles;

} /* namespace Profile */
#endif /* PROFILE_H_ */
