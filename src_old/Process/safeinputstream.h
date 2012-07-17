/* ---------------------------------------------------------------------------
** Author: Martin Geier
** safeinputstream.h is part of ProcessExecutor.
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

#ifndef SAFEINPUTSTREAM_H_
#define SAFEINPUTSTREAM_H_

#include "safestream.h"

namespace Process {

class SafeInputStream {
public:
	SafeInputStream(SafeStream &stream);
	virtual ~SafeInputStream();
	bool isOpen();
	bool operator>>(std::string &text);
	int operator>>=(std::string &text);
	void enableNonBlockMode();
	void disableNonBlockMode();
private:
	SafeInputStream(const SafeInputStream& stream);
	void operator=(const SafeInputStream& stream);
	SafeStream &stream;
};

} /* namespace Process */
#endif /* SAFEINPUTSTREAM_H_ */
