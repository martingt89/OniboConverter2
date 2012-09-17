/* ---------------------------------------------------------------------------
** Author: Martin Geier
** dispenser.h is part of OniboConverter2.
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

#ifndef DISPENSER_H_
#define DISPENSER_H_

#include <deque>
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
	Dispenser();
	virtual ~Dispenser();
	void processMediaFiles(const std::list<MediaFile::MediaFile*>& files, const int& numOfThreads, bool fileThreading);
private:
	bool getNextMediaFile(MediaFile::MediaFile*& mediaFile);
	void run();
	int numberOfThreads;
	bool enableFileThreading;
	std::deque<MediaFile::MediaFile*> filesToProcessing;
	std::list<std::thread*> processThreads;
	std::mutex mutex;
};

} /* namespace Converter */
#endif /* DISPENSER_H_ */
