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
#include "../CppExtension/path.h"
#include "videostream.h"
#include "audiostream.h"
#include "../Converter/convertsettings.h"
#include <thread>

namespace MediaFile {

class MediaFile {
public:
	enum State{
		NOT_SET, OK, NOT_FOUND, INVALID_FORMAT
	};
	enum ConvertFileState{
		WAITING, PROCESSING, FINISH, INVALID_FILE, ABORT, OVERWRITE, FAIL
	};
	struct FileInfo{
		State fileState;
		double duration;
		double startTime;
		std::string bitrate;
		std::vector<VideoStream> videos;
		std::vector<AudioStream> audios;
	};
public:
	MediaFile(Path filePath, int fileId);
	MediaFile(const MediaFile& file);
	virtual ~MediaFile();
	void setSettingsList(const Converter::ConvertSettingsList& settingsList);
	void setDestinationPath(const Path& destinationPath);
	void setContainerName(const std::string& containerName);
	bool scanMediaFile();
	bool isSet();
	bool isValid();
	FileInfo getFileInfo();
	Path getPath() const;
//	void setMetadata(std::string key, std::string value);
	void clearConvertStatus();
	void convert();
	std::string getShortName();
	std::string getRemainingTime();
	int getPercentage();
	std::string getConvertStateAsString();
	ConvertFileState getConvertState();
	int getFileId();
	bool isEnded();

	void abort();
	void enableOverwriteFile();
	Path getOutputFilePath();
	void setName(const std::string& fileName);
	std::string getContainerName();
	void setOverwievState();
private:
	std::string timeToHHMMSS(int localTime);
	std::mutex mutex;
	std::condition_variable condition;
	Path filePath;
	int fileId;
	FileInfo fileInfo;
	bool set;
	bool valid;
	bool isAbort;
	Converter::ConvertSettingsList settingsList;
	volatile bool enableOverwrite;
	std::string fileName;
	std::string containerName;
	Path destinationPath;
	//
	ConvertFileState status;
	double fraction;
	int remainingTime;
	ProcessExecutor::Process* process;
};

} /* namespace MediaFile */
#endif /* MEDIAFILE_H_ */
