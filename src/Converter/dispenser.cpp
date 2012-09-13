/*
 * dispenser.cpp
 *
 *  Created on: 21.8.2012
 *      Author: martint
 */

#include "dispenser.h"
#include <iostream>

namespace Converter {

Dispenser::Dispenser() {
	numberOfThreads = 1;
	enableFileThreading = false;
}

Dispenser::~Dispenser() {}

void Dispenser::processMediaFiles(const std::list<MediaFile::MediaFile*>& files,
		const int& numOfThreads, bool fileThreading){
	numberOfThreads = numOfThreads;
	enableFileThreading = false;
	int numOfSupportedThreading = 0;
	for (auto file : files){
		filesToProcessing.push_back(file);
		if(file->supportThreding()){
			numOfSupportedThreading++;
		}
	}
	if(fileThreading && numOfSupportedThreading > 0){
		enableFileThreading = true;
	}
	if(enableFileThreading){
		processThreads.push_back(new std::thread(&Dispenser::run, this));
	}else{
		for(int i = 0; i < numberOfThreads; ++i){
			processThreads.push_back(new std::thread(&Dispenser::run, this));
		}
	}
	return;
}
void Dispenser::run(){
	MediaFile::MediaFile* file = NULL;
	while(getNextMediaFile(file)){
		if(file->getMediaInfo().getScanStatus() == MediaFile::MediaInfo::NOSCAN){
			file->getMediaInfo().scanMediaFile();
		}
		file->convert(enableFileThreading, numberOfThreads);
	}
}
bool Dispenser::getNextMediaFile(MediaFile::MediaFile*& mediaFile){
	std::unique_lock<std::mutex> lock(mutex);
	if(filesToProcessing.empty()){
		return false;
	}
	MediaFile::MediaFile* file;
	int counter = 0;
	int maxCycles = filesToProcessing.size();
	while(!filesToProcessing.empty()){
		file = filesToProcessing.front();
		filesToProcessing.pop_front();
		if(!file->getMediaConvert()->getOutputFilePath().exist() || counter == maxCycles){
			mediaFile = file;
			return true;
		}else{
			file->getMediaConvert()->setOverwievState();
			filesToProcessing.push_back(file);
		}
		++counter;
	}
	return false;
}
} /* namespace Converter */
