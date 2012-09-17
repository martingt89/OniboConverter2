/* ---------------------------------------------------------------------------
** Author: Martin Geier
** mediainfo.h is part of OniboConverter2.
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

#ifndef MEDIAINFO_H_
#define MEDIAINFO_H_

#include "../CppExtension/path.h"
#include "videostream.h"
#include "audiostream.h"
#include <string>
#include <vector>


namespace MediaFile {

class MediaInfo {
public:
	enum ScanStatus{
		NOSCAN, OK, INVALID
	};
	MediaInfo(const Path& mediaPath);
	virtual ~MediaInfo();
	ScanStatus scanMediaFile();

	double getDuration() const;
	double getStartTime() const;
	std::string getBitrate() const;
	std::vector<VideoStream> getVideoStreams() const;
	std::vector<AudioStream> getAudioStreams() const;
	ScanStatus getScanStatus() const;
private:
	Path mediaPath;
	ScanStatus scanStatus;
	double duration;
	double startTime;
	std::string bitrate;
	std::vector<VideoStream> videos;
	std::vector<AudioStream> audios;
};

} /* namespace MediaFile */
#endif /* MEDIAINFO_H_ */
