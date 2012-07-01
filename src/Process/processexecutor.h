/* ---------------------------------------------------------------------------
** Author: Martin Geier
** processexecutor.h is part of ProcessExecutor.
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

#ifndef PROCESSEXECUTOR_H_
#define PROCESSEXECUTOR_H_

#include <iostream>
#include <sstream>
#include "safestream.h"
#include "safeoutputstream.h"
#include "safeinputstream.h"
#include <thread>
#include <list>

namespace Process {

class Executor {
public:
	Executor(const std::string& path, const std::list<std::string>& args = std::list<std::string>());
	virtual ~Executor();
	SafeInputStream& getStdOut();
	SafeInputStream& getStdErr();
	SafeOutputStream& getStdIn();
	SafeInputStream& getLog();
	int waitForRunChild();
	int waitForEndChild();
	void terminateChild();
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
	int errorState;
	bool rerunParent;
	bool endChild;
};

} /* namespace Process */
#endif /* PROCESSEXECUTOR_H_ */
