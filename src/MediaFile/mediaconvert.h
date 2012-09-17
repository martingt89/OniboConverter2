/* ---------------------------------------------------------------------------
** Author: Martin Geier
** mediaconvert.h is part of OniboConverter2.
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
