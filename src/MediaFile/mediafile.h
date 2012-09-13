/*
 * mediafile.h
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */

#ifndef MEDIAFILE_H_
#define MEDIAFILE_H_

namespace ProcessExecutor{
	class Process;
}

#include <string>
#include <vector>
#include <stdexcept>
#include "videostream.h"
#include "audiostream.h"
#include <thread>
#include <sstream>
#include "mediainfo.h"
#include "mediaconvert.h"
#include "../CppExtension/path.h"
#include "../Profile/profile.h"
#include <memory>

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
