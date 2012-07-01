/* ---------------------------------------------------------------------------
** Author: Martin Geier
** safestream.h is part of ProcessExecutor.
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

#ifndef SAFESTREAM_H_
#define SAFESTREAM_H_

#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <list>
namespace Process {

class SafeStream{
public:
	SafeStream();
	virtual ~SafeStream();
	bool operator<<(const std::string& text);
	bool operator>>(std::string& text);
	int operator>>=(std::string& text);
	bool isOpen();
	void close();
private:
	bool open;
	std::mutex mutex;
	std::condition_variable cond;
	std::list<std::string> buffer;
};

} /* namespace Process */
#endif /* SAFESTREAM_H_ */
