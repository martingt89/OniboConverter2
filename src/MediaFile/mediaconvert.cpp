/*
 * mediaconvert.cpp
 *
 *  Created on: 13.9.2012
 *      Author: martin
 */

#include "mediaconvert.h"
#include "../helper.h"
#include "../userpreferences.h"

namespace MediaFile {

const static std::string STATE_OK="OK";
const static std::string STATE_WAITING="waiting";
const static std::string STATE_PROCESSING="processing";
const static std::string STATE_INVALID="invalid file";
const static std::string STATE_ABORT="abort";
const static std::string STATE_OVERWRITE="overwrite?";
const static std::string STATE_FAIL="fail";

const static std::string UNKNOWN_REMAINING_TIME = "Unknown";

MediaConvert::MediaConvert(){
	init();
}

MediaConvert::~MediaConvert() {
	// TODO Auto-generated destructor stub
}

void MediaConvert::init(){
	convertState = WAITING;
	fraction = 0;
	remainingTime = -1;
	enableOverwrite = false;
	fileName = mediaPath.getLastPathPart();
	isAbort = false;
	process = 0;
}
Path MediaConvert::getOutputFilePath(){
	return Path(destination.getPath(), (fileName + "." + getContainerName()));
}

std::string MediaConvert::getContainerName(){
	return container;
}
void MediaConvert::setNewName(const std::string& fileName){
	std::unique_lock<std::mutex> uniqueLock(mutex);
	convertState = WAITING;
	this->fileName = fileName;
	condition.notify_one();
}
std::string MediaConvert::getRemainingTime() {
	if(remainingTime < 0){
		return UNKNOWN_REMAINING_TIME;
	}
	return secTimeToReadableTime(remainingTime);
}
int MediaConvert::getPercentage(){
	return (fraction)*100+0.5;
}
std::string MediaConvert::getConvertStateAsString(){
	switch(convertState){
	case WAITING: return STATE_WAITING;
	case PROCESSING: return STATE_PROCESSING;
	case FINISH: return STATE_OK;
	case ABORT: return STATE_ABORT;
	case OVERWRITE: return STATE_OVERWRITE;
	case FAIL: return STATE_FAIL;
	default: return STATE_INVALID;
	}
	return STATE_INVALID;
}

MediaConvert::ConvertState MediaConvert::getConvertState(){
	std::unique_lock<std::mutex> uniqueLock(mutex);
	return convertState;
}

bool MediaConvert::isEnded(){
	return (convertState == FINISH) ||
			(convertState == INVALID_FILE) ||
			(convertState == ABORT) ||
			(convertState == FAIL);
}

void MediaConvert::abort(){
	std::unique_lock<std::mutex> uniqueLock(mutex);
	if(!isEnded()){
		isAbort = true;
		convertState = ABORT;
		if(process != 0){
			process->terminateProcess();
		}
	}
	condition.notify_one();
}
//
//
void MediaConvert::setOverwievState(){
	std::unique_lock<std::mutex> uniqueLock(mutex);
	convertState = OVERWRITE;
}
std::string MediaConvert::getOutput(){
	return errorOutputBuffer.str();
}
void MediaConvert::enableOverwriteFile(){
	std::unique_lock<std::mutex> uniqueLock(mutex);
	convertState = WAITING;
	enableOverwrite = true;
	condition.notify_one();
}
void MediaConvert::convert(const bool enableFileThreading, const int numOfThreads, bool valid, double duration){
	if(valid){
		std::unique_lock<std::mutex> uniqueLock(mutex);
		while(this->getOutputFilePath().exist() && !enableOverwrite && !isAbort){
			convertState = OVERWRITE;
			condition.wait(uniqueLock);
		}
		if(isAbort){
			convertState = ABORT;
			return;
		}

		convertState = PROCESSING;

		generator.setThreading(enableFileThreading, numOfThreads);

		std::list<std::string> arguments = generator.generate();
		arguments.push_front("-y");
		arguments.push_front(mediaPath.getPath());
		arguments.push_front("-i");
		arguments.push_back(getOutputFilePath().getPath());
		auto extConverter = UserPreferences::getInstance()->getExtConverterPath();
		std::stringstream textCommand;
		textCommand<<"command:"<<std::endl;
		textCommand<<extConverter.getPath();
		for(auto x : arguments){
			textCommand<<" "<<x;
		}
		textCommand<<std::endl<<std::endl;
		errorOutputBuffer << textCommand.str();
		Converter::ConvertParser parser(duration);
		process = new ProcessExecutor::Process(extConverter.getPath(), arguments);
		process->waitForProcessBegin();
		uniqueLock.unlock();
		auto& stderr = process->getStdErr();
		std::string line;
		while(stderr >> line){
			double tmpFraction = 0;
			int tmpTime = 0;
			bool processOk = parser.processLine(line, tmpFraction, tmpTime);
			if(processOk){
				fraction = tmpFraction;
				if(tmpTime > 0){
					remainingTime = tmpTime;
				}
			}else{
				errorOutputBuffer << line << std::endl;
			}
		}
		int res = process->waitForProcessEnd();
		if(res != 0){
			convertState = FAIL;
		}else{
			convertState = FINISH;
		}
		fraction = 1;
		remainingTime = 0;
		uniqueLock.lock();
		delete process;
		process = NULL;
		uniqueLock.unlock();
	}else{
		convertState = INVALID_FILE;
	}
}
void MediaConvert::setPath(const Path& mediaPath){
	this->mediaPath = mediaPath;
	init();
}
void MediaConvert::setDestination(const Path& destination){
	this->destination = destination;
	init();
}
void MediaConvert::setContainerName(const std::string& containerName){
	this->container = containerName;
	init();
}
void MediaConvert::setGenerator (Converter::ArgumentsGenerator generator){
	this->generator = generator;
	init();
}
} /* namespace MediaFile */
