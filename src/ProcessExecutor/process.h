/* ---------------------------------------------------------------------------
** Author: Martin Geier
** process.h is part of ProcessExecutor.
**
** ProcessExecutor is free software: you can redistribute it and/or modify
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

#ifndef PROCESS_H_
#define PROCESS_H_

#include <iostream>
#include <sstream>
#include "safestream.h"
#include "safeoutputstream.h"
#include "safeinputstream.h"
#include <thread>
#include <list>

namespace ProcessExecutor {

class Process {
public:
	enum ProcessState{
		PROCESS_STATE_OK,
		PROCESS_STATE_PIPEERR,
		PROCESS_STATE_VFORKERR,
		PROCESS_STATE_DUP0ERR,
		PROCESS_STATE_DUP1ERR,
		PROCESS_STATE_DUP2ERR,
		PROCESS_STATE_EXECVPERR
	};
public:
	Process(const std::string& path, const std::list<std::string>& args = std::list<std::string>());
	virtual ~Process();
	SafeInputStream& getStdOut();
	SafeInputStream& getStdErr();
	SafeOutputStream& getStdIn();
	SafeInputStream& getLog();
	int waitForProcessBegin();
	int waitForProcessEnd();
	void terminateProcess();
private:
	SafeStream out;
	SafeStream err;
	SafeStream in;
	SafeStream log;
	SafeInputStream errStream;
	SafeInputStream outStream;
	SafeInputStream logStream;
	SafeOutputStream inStream;

	void run();
	void writeIn(int fd);
	void readOut(int fd);
	void readErr(int fd);
	void readFdWriteToStream(int fd, SafeStream &stream);
	std::thread* thread;
	std::mutex mutex;
	std::condition_variable cond;
	std::string command;
	std::list<std::string> args;

	int childPid;
	int childReturnState;
	ProcessState processState;
	bool rerunParent;
	bool endChild;
};

} /* namespace ProcessExecutor */
#endif /* PROCESS_H_ */
