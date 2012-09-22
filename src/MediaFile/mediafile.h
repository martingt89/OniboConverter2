/* ---------------------------------------------------------------------------
** Author: Martin Geier
** mediafile.h is part of OniboConverter2.
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

#ifndef MEDIAFILE_H_
#define MEDIAFILE_H_

namespace ProcessExecutor{
	class Process;
}

#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include <thread>
#include <sstream>
#include "mediainfo.h"
#include "mediaconvert.h"
#include "../CppExtension/path.h"
#include "../Profile/profile.h"

namespace MediaFile {

class MediaFile {
public:
	MediaFile(const Path& filePath,  const int& fileId);
	virtual ~MediaFile();
	MediaInfo& getMediaInfo();
	std::shared_ptr<MediaConvert> getMediaConvert();
	Path getPath() const;
	void setDestinationPath(const Path& destinationPath);
	void setActualProfile(const Profile::Profile& profile);
	std::string getShortName();
	int getFileId();
	bool supportThreding() const;
	void convert(bool enableFileThreading, int numberOfThreads);
private:
	MediaInfo mediaInfo;
	Path filePath;
	int fileId;
	std::shared_ptr<MediaConvert> mediaConvert;
	Path destinationPath;
	Profile::Profile profile;
};

} /* namespace MediaFile */
#endif /* MEDIAFILE_H_ */
