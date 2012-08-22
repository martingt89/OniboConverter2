/* ---------------------------------------------------------------------------
** Author: Martin Geier
** process.cpp is part of ProcessExecutor.
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

#include "process.h"
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <cstdlib>

namespace ProcessExecutor {

std::string getErrorMessage(const std::string& text){
	return text + strerror(errno);
}

Process::Process(const std::string& path, const std::list<std::string>& args):
		errStream(err),
		outStream(out),
		logStream(log),
		inStream(in),
		args(args){
	processState = PROCESS_STATE_OK;
	childReturnState = -1;
	childPid = -1;
	rerunParent = false;
	endChild = false;

	command = path;
	thread = new std::thread(&Process::run, this);
}

Process::~Process() {
	thread->join();
	delete thread;
}
SafeInputStream& Process::getStdOut(){
	return outStream;
}
SafeInputStream& Process::getStdErr(){
	return errStream;
}
SafeOutputStream& Process::getStdIn(){
	return inStream;
}
SafeInputStream& Process::getLog(){
	return logStream;
}

int Process::waitForProcessBegin(){
	std::unique_lock<std::mutex> m(mutex);
	while(!rerunParent){
		cond.wait(m);
	}
	if(processState != PROCESS_STATE_OK){
		return 1;
	}
	return 0;
}
int Process::waitForProcessEnd(){
	std::unique_lock<std::mutex> m(mutex);
	while(!rerunParent || !endChild){
		cond.wait(m);
	}
	return childReturnState;
}
void Process::terminateProcess(){
	std::unique_lock<std::mutex> m(mutex);
	if(childPid > 0){
		kill(childPid, SIGTERM);
	}else{
		//Process is not running
	}
}
void Process::writeIn(int fd){
	std::string input;
	while (in >> input){
		ssize_t numberOfWritedChars = write (fd, input.c_str(), input.size());
		if(numberOfWritedChars != (ssize_t)input.size()){
			log << std::string("Error: write cannot send a command: ") + input;
		}
	}
}

void Process::readFdWriteToStream(int fd, SafeStream &stream) {
	char charBuffer;
	std::stringstream lineBuffer;
	while (read(fd, &charBuffer, 1) || lineBuffer.str().size() > 0) {
		if (charBuffer != '\n') {
			lineBuffer << charBuffer;
		} else {
			stream << lineBuffer.str();
			lineBuffer.str("");
		}
		charBuffer = '\n';	//if not read new char, end line
	}
}
void Process::readOut(int fd){
	readFdWriteToStream(fd, out);
}
void Process::readErr(int fd) {
	readFdWriteToStream(fd, err);
}

/*Fork process, start program with command and args*/
void Process::run() {
	int toInt[2];
	int toOut[2];
	int toErr[2];
	if (pipe(toInt) != 0) {
		processState = PROCESS_STATE_PIPEERR;
		log << getErrorMessage("Cannot create pipe: ");
		return;
	}
	if (pipe(toOut) != 0) {
		processState = PROCESS_STATE_PIPEERR;
		log << getErrorMessage("Cannot create pipe: ");
		return;
	}
	if (pipe(toErr) != 0) {
		processState = PROCESS_STATE_PIPEERR;
		log << getErrorMessage("Cannot create pipe: ");
		return;
	}

	std::list<std::string>::iterator it;
	char** comm = (char**)malloc(sizeof(char*)*(args.size() + 2));
	comm[0] = (char*) (command.c_str());
	int cc = 1;
	for (it = args.begin(); it != args.end(); it++) {
		comm[cc] = (char*) (it->c_str());
		cc++;
	}
	comm[cc] = NULL;

	int vforkErr = 0;

	int pid = vfork();
	if (pid == -1) {
		processState = PROCESS_STATE_VFORKERR;
		log << getErrorMessage("Cannot run vfork: ");
		free(comm);
		return;
	}

	if(pid == 0){	//child
		close(0);
		if(dup(toInt[0]) != 0){
			processState = PROCESS_STATE_DUP0ERR;
			log << getErrorMessage("Dup 0 error: ");
			_exit(1);
		}
		close(toInt[1]);

		close(1);
		if(dup(toOut[1]) != 1){
			processState = PROCESS_STATE_DUP1ERR;
			log << getErrorMessage("Dup 1 error: ");
			_exit(1);
		}
		close(toOut[0]);

		close(2);
		if(dup(toErr[1]) != 2){
			processState = PROCESS_STATE_DUP2ERR;
			log << getErrorMessage("Dup 2 error: ");
			_exit(1);
		}
		close(toErr[0]);

		execvp(command.c_str(), comm);
		{
			processState = PROCESS_STATE_EXECVPERR;
			log << getErrorMessage("execvp error: ");
			vforkErr = 1;
		}
		_exit(1);
	}

	//parent

	close(toErr[1]);
	close(toOut[1]);
	close(toInt[0]);
	std::unique_lock<std::mutex> m(mutex);
	childPid = pid;
	rerunParent = true;
	cond.notify_all();
	m.unlock();

	if(vforkErr == 0){	//command is running
		std::thread threadIn(&Process::writeIn, this, toInt[1]);
		std::thread threadOut(&Process::readOut, this, toOut[0]);
		std::thread threadErr(&Process::readErr, this, toErr[0]);

		threadOut.join();
		threadErr.join();
		in.close();
		err.close();
		out.close();
		threadIn.join();
		wait(&childReturnState);
	}
	m.lock();
	childPid = -1;
	endChild = true;
	cond.notify_all();
	m.unlock();

	free(comm);
	in.close();
	err.close();
	out.close();
	log.close();
}


} /* namespace ProcessExecutor */
