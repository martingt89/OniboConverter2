/* ---------------------------------------------------------------------------
** Author: Martin Geier
** profile.h is part of OniboConverter2.
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

#ifndef PROFILE_H_
#define PROFILE_H_

#include <string>
#include <list>
#include "../CppExtension/hashmap.h"
#include "../MediaElement/mediaelements.h"

namespace Profile {

class Profile {
public:
	struct ManualSettings{
		std::string command;
		std::list<std::string> args;
	};
public:
	Profile(const std::string& name);
	Profile();
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
	void getManualSettings(std::list<ManualSettings>& manualSettings) const;
//-----------==============------------------=====================------------------==================
	void setContainer(const MediaElement::Container& container);
	void setVideoMode(const int& row);
	void setVideoFormat(const MediaElement::Format& videoFormat);
	void setVideoEncoder(const MediaElement::Encoder& videoEncoder);
	void setVideoBitrate(const MediaElement::Bitrate& videoBitrate);
	void setVideoResolution(const MediaElement::Resolution& resolution);
	void setVideoFFpreset(const MediaElement::FFpreset& ffpreset);
	void setVideoFramerate(const MediaElement::Framerate& framerate);
	//
	void setAudioMode(const int& row);
	void setAudioFormat(const MediaElement::Format& audioFormat);
	void setAudioEncoder(const MediaElement::Encoder& audioEncoder);
	void setAudioGrade(const MediaElement::AudioGrade& audioGrade);
	void setAudioSamplerate(const MediaElement::Samplerate& audioSamplerate);
	void setAudioChannel(const MediaElement::Channel& audioChannel);
	//
	void setManualSettings(const std::list<ManualSettings>& manualSettings);
	void addManualSettings(const ManualSettings& manualSettings);
private:
	std::string profileName;
	MediaElement::Container container;
	bool isContainer;
	//
	int videoMode;
	bool isVideoMode;
	MediaElement::Format videoFormat;
	bool isVideoFormat;
	MediaElement::Encoder videoEncoder;
	bool isVideoEncoder;
	MediaElement::Bitrate videoBitrate;
	bool isVideoBitrate;
	MediaElement::Resolution resolution;
	bool isResolution;
	MediaElement::FFpreset ffpreset;
	bool isFFPreset;
	MediaElement::Framerate framerate;
	bool isFramerate;
	//
	int audioMode;
	bool isAudioMode;
	MediaElement::Format audioFormat;
	bool isAudioFormat;
	MediaElement::Encoder audioEncoder;
	bool isAudioEncoder;
	MediaElement::AudioGrade audioGrade;
	bool isAudioGrade;
	MediaElement::Samplerate samplerate;
	bool isSamplerate;
	MediaElement::Channel channel;
	bool isChannel;
	std::list<ManualSettings> settings;
};

//typedef std::list<Profile> Profiles;

} /* namespace Profile */
#endif /* PROFILE_H_ */
