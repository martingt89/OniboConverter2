/*
 * dispenser.h
 *
 *  Created on: 21.8.2012
 *      Author: martint
 */

#ifndef DISPENSER_H_
#define DISPENSER_H_

#include <queue>
#include <list>
#include "../CppExtension/path.h"
#include "../MediaFile/mediafile.h"
#include <thread>

namespace Converter {

class Dispenser {
public:
	enum ConvertFilesState{
		WAITING, PROCESSING, FINISH, INVALID_FILE
	};
	struct FileState{
		ConvertFilesState status;
		double fraction;
		Path filePath;
		int remainingTime;
		int fileID;
	};
public:
	Dispenser(const int numberOfThreads = 1, const bool enableFileThreading = false);
	virtual ~Dispenser();
	void processMediaFiles(const std::list<MediaFile::MediaFile*>& files);
private:
	bool getNextMediaFile(MediaFile::MediaFile*& mediaFile);
	void run();
	int numberOfThreads;
	bool enableFileThreading;
	std::queue<MediaFile::MediaFile*> filesToProcessing;
	std::list<std::thread*> processThreads;
	std::mutex mutex;
};

} /* namespace Converter */
#endif /* DISPENSER_H_ */
