/* ---------------------------------------------------------------------------
** Author: Martin Geier
** safeoutputstream.h is part of ProcessExecutor.
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

#ifndef SAFEOUTPUTSTREAM_H_
#define SAFEOUTPUTSTREAM_H_

#include "safestream.h"

namespace Process {

class SafeOutputStream {
public:
	SafeOutputStream(SafeStream &stream);
	virtual ~SafeOutputStream();
	bool isOpen();
	void close();
	bool operator<<(std::string &text);
private:
	SafeStream &stream;
	SafeOutputStream(const SafeOutputStream &stream);
	void operator=(const SafeOutputStream &stream);
};

} /* namespace Process */
#endif /* SAFEOUTPUTSTREAM_H_ */
