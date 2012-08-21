/*
 * dispenser.cpp
 *
 *  Created on: 21.8.2012
 *      Author: martint
 */

#include "dispenser.h"

namespace Converter {

Dispenser::Dispenser(const int numberOfThreads, const bool enableFileThreading) :
		numberOfThreads(numberOfThreads), enableFileThreading(enableFileThreading){
}

Dispenser::~Dispenser() {}

void Dispenser::processMediaFiles(const std::list<MediaFile::MediaFile*>& files){
	for (auto file : files){
		filesToProcessing.push(file);
	}
	if(!enableFileThreading){
		for(int i = 0; i < numberOfThreads; ++i){
			processThreads.push_back(new std::thread(&Dispenser::run, this));
		}
	}
	return;
}
void Dispenser::run(){
	MediaFile::MediaFile* file;
	while(getNextMediaFile(file)){
		file->convert();
	}
}
bool Dispenser::getNextMediaFile(MediaFile::MediaFile*& mediaFile){
	std::unique_lock<std::mutex> lock(mutex);
	if(filesToProcessing.empty()){
		return false;
	}
	mediaFile = filesToProcessing.front();
	filesToProcessing.pop();
	return true;
}
} /* namespace Converter */
