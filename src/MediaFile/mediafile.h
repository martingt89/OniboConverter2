/*
 * mediafile.h
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */

#ifndef MEDIAFILE_H_
#define MEDIAFILE_H_

#include <string>
#include <vector>
#include <stdexcept>
#include "../CppExtension/path.h"
#include "videostream.h"
#include "audiostream.h"
#include "../Converter/convertsettings.h"

namespace MediaFile {

class MediaFile {
public:
	enum State{
		NOT_SET, OK, NOT_FOUND, INVALID_FORMAT
	};
	struct FileInfo{
		State fileState;
		double duration;
		double startTime;
		std::string bitrate;
		std::vector<VideoStream> videos;
		std::vector<AudioStream> audios;
	};
	enum ConvertFileState{
		WAITING, PROCESSING, FINISH, INVALID_FILE
	};
public:
	MediaFile(Path filePath, int fileId);
	virtual ~MediaFile();
	void setSettingsList(const Converter::ConvertSettingsList& settingsList);
	bool scanMediaFile();
	bool isSet();
	bool isValid();
	FileInfo getFileInfo();
//	void setMetadata(std::string key, std::string value);
	void clearConvertStatus();
	void convert();
	std::string getShortName();
	std::string getRemainingTime();
	int getPercentage();
	std::string getConvertState();
	int getFileId();
	bool isEnded();
private:
	Path filePath;
	int fileId;
	FileInfo fileInfo;
	bool set;
	bool valid;
	Converter::ConvertSettingsList settingsList;
	//
	ConvertFileState status;
	double fraction;
	int remainingTime;
};

} /* namespace MediaFile */
#endif /* MEDIAFILE_H_ */
