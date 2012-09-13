/*
 * mediaconvert.h
 *
 *  Created on: 13.9.2012
 *      Author: martin
 */

#ifndef MEDIACONVERT_H_
#define MEDIACONVERT_H_

#include <string>
#include <vector>
#include <sstream>
#include "mediainfo.h"
#include "../CppExtension/path.h"
#include "../ProcessExecutor/process.h"
#include "../Converter/convertparser.h"
#include "../Converter/argumentsgenerator.h"

namespace MediaFile {

class MediaConvert {
public:
	enum ConvertState{
		WAITING, PROCESSING, FINISH, INVALID_FILE, ABORT, OVERWRITE, FAIL
	};
	MediaConvert();
	virtual ~MediaConvert();
	void set(const Path& mediaPath, const Path& destination, const std::string& container,
			const double& duration, const bool& valid, Converter::ArgumentsGenerator& generator);
	void setNewName(const std::string& newName);
	std::string getConvertStateAsString();
	std::string getRemainingTime();
	int getPercentage();
	MediaConvert::ConvertState getConvertState();
	bool isEnded();
	void abort();
	std::string getOutput();
	void enableOverwriteFile();
	Path getOutputFilePath();
	std::string getContainerName();
	void setOverwievState();
	void convert(const bool enableFileThreading, const int numOfThreads, bool valid, double duration);
	void setPath(const Path& mediaPath);
	void setDestination(const Path& destination);
	void setContainerName(const std::string& containerName);
	void setGenerator (Converter::ArgumentsGenerator generator);
private:
	void init();
	Path mediaPath;
	Path destination;
	std::string container;
	Converter::ArgumentsGenerator generator;

	std::stringstream errorOutputBuffer;
	std::mutex mutex;
	std::condition_variable condition;
	bool isAbort;
	volatile bool enableOverwrite;
	std::string fileName;
	//
	ConvertState convertState;
	double fraction;
	int remainingTime;
	ProcessExecutor::Process* process;
};

} /* namespace MediaFile */
#endif /* MEDIACONVERT_H_ */
