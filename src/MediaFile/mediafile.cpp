/*
 * mediafile.cpp
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */

//TODO refactor, switch to more classes

#include "mediafile.h"

#include "mediafilescanner.h"
#include "../Converter/convertparser.h"
#include "../helper.h"
#include "../userpreferences.h"
#include "../ProcessExecutor/process.h"

namespace MediaFile {

const static std::string STATE_OK="OK";
const static std::string STATE_WAITING="waiting";
const static std::string STATE_PROCESSING="processing";
const static std::string STATE_INVALID="invalid file";
const static std::string STATE_ABORT="abort";
const static std::string STATE_OVERWRITE="overwrite?";
const static std::string STATE_FAIL="fail";

const static int ONE_HOUR = 3600;
const static int ONE_MINIT = 60;
const static std::string UNKNOWN_REMAINING_TIME = "Unknown";

MediaFile::MediaFile(Path filePath,  int fileId) : filePath(filePath) ,fileId(fileId) {
	fileInfo.duration = -1;
	fileInfo.fileState = NOT_SET;
	fileInfo.startTime = -1;
	fileInfo.bitrate = "";
	set = false;
	valid = false;
	isAbort = false;
	enableOverwrite = false;
	clearConvertStatus();
	process = NULL;
}
MediaFile::MediaFile(const MediaFile& file){
	this->filePath = file.filePath;
	this->fileId = file.fileId;
	this->fileInfo = file.fileInfo;
	this->set = file.set;
	this->valid = file.valid;
	this->settingsList = file.settingsList;
	this->status = file.status;
	this->fraction = file.fraction;
	this->remainingTime = file.remainingTime;
	this->enableOverwrite = file.enableOverwrite;
	this->isAbort = file.isAbort;
	this->process = file.process;
}

MediaFile::~MediaFile() {}

bool MediaFile::scanMediaFile(){
	if(!set){
		set = true;
		fileInfo.videos.clear();
		fileInfo.audios.clear();

		MediaFileScanner scanner(filePath);
		if(scanner.getFinalStatus() == MediaFileScanner::OK_RESULT){
			valid = true;
			fileInfo.startTime = scanner.getStartTime();
			fileInfo.duration = scanner.getDuration();
			fileInfo.bitrate = scanner.getBitrate();
			//todo getmetadata
			auto videoStreams = scanner.getVideoStreams();
			for(auto stream : videoStreams){
				fileInfo.videos.push_back(stream);
			}
			auto audioStreams = scanner.getAudioStreams();
			for(auto stream : audioStreams){
				fileInfo.audios.push_back(stream);
			}
		}else{
//			std::cout<<"Invaid file"<<std::endl;
			return false;
		}
		return true;
	}
	return false;
}
bool MediaFile::isSet(){
	return set;
}
bool MediaFile::isValid(){
	return valid;
}
MediaFile::FileInfo MediaFile::getFileInfo(){
	return fileInfo;
}
Path MediaFile::getPath() const {
	return filePath;
}
void MediaFile::setSettingsList(const Converter::ConvertSettingsList& settingsList){
	this->settingsList = settingsList;
	this->containerName = settingsList.getContainerName();
}
void MediaFile::setDestinationPath(const Path& destinationPath){
	this->destinationPath = destinationPath;
}
void MediaFile::setContainerName(const std::string& containerName){
	this->containerName = containerName;
}
void MediaFile::clearConvertStatus(){
	status = WAITING;
	fraction = 0;
	remainingTime = -1;
	enableOverwrite = false;
	fileName = filePath.getLastPathPart();
	isAbort = false;
	errorOutputBuffer.clear();
}
void MediaFile::convert(){
	if(valid){
		std::unique_lock<std::mutex> uniqueLock(mutex);
		while(this->getOutputFilePath().exist() && !enableOverwrite && !isAbort){
			status = OVERWRITE;
			condition.wait(uniqueLock);
		}
		if(isAbort){
			status = ABORT;
			return;
		}
		status = PROCESSING;

		std::list<std::string> arguments;
		arguments.push_back("-i");
		arguments.push_back(filePath.getPath());
		arguments.push_back("-y");
		auto args = settingsList.getArguments();
		for(auto x : args){
			arguments.push_back(x);
		}
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

		Converter::ConvertParser parser(fileInfo.duration);
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
			status = FAIL;
		}else{
			status = FINISH;
		}
		fraction = 1;
		remainingTime = 0;
		uniqueLock.lock();
		delete process;
		process = NULL;
		uniqueLock.unlock();
	}else{
		status = INVALID_FILE;
	}
}
std::string MediaFile::getShortName(){
	return filePath.getLastPathPart().substr(0, 30);
}

std::string MediaFile::getRemainingTime() {
	if(remainingTime < 0){
		return UNKNOWN_REMAINING_TIME;
	}
	return timeToHHMMSS(remainingTime);
}
int MediaFile::getPercentage(){
	return (fraction)*100+0.5;
}
std::string MediaFile::getConvertStateAsString(){
	switch(status){
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
MediaFile::ConvertFileState MediaFile::getConvertState(){
	std::unique_lock<std::mutex> uniqueLock(mutex);
	return status;
}
int MediaFile::getFileId(){
	return fileId;
}
bool MediaFile::isEnded(){
	return (status == FINISH) || (status == INVALID_FILE) || (status == ABORT) || (status == FAIL);
}
void MediaFile::abort(){
	std::unique_lock<std::mutex> uniqueLock(mutex);
	if(!isEnded()){
		isAbort = true;
		status = ABORT;
		if(process != NULL){
			process->terminateProcess();
		}
	}
	condition.notify_one();
}

void MediaFile::setName(const std::string& fileName){
	std::unique_lock<std::mutex> uniqueLock(mutex);
	status = WAITING;
	this->fileName = fileName;
	condition.notify_one();
}
std::string MediaFile::getContainerName(){
	return containerName;
}
void MediaFile::setOverwievState(){
	status = OVERWRITE;
}
std::string MediaFile::getErrorOutput(){
	return errorOutputBuffer.str();
}
void MediaFile::enableOverwriteFile(){
	std::unique_lock<std::mutex> uniqueLock(mutex);
	status = WAITING;
	enableOverwrite = true;
	condition.notify_one();
}

Path MediaFile::getOutputFilePath(){
	return Path(destinationPath.getPath(), (fileName + "." + containerName));
}

std::string MediaFile::timeToHHMMSS(int localTime) {
	int hours = localTime / ONE_HOUR;
	localTime -= hours * ONE_HOUR;
	int minits = localTime / ONE_MINIT;
	localTime -= minits * ONE_MINIT;
	std::string time = "";
	if (hours < 10) {
		time += "0";
	}
	time += toS(hours) + ":";
	if (minits < 10) {
		time += "0";
	}
	time += toS(minits) + ":";
	if (localTime < 10) {
		time += "0";
	}
	time += toS(localTime);
	return time;
}
//void MediaFile::setMetadata(std::string key, std::string value){
//	metadata[key] = value;
//}

} /* namespace MediaFile */
