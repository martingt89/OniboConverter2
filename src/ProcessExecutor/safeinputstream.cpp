/* ---------------------------------------------------------------------------
** Author: Martin Geier
** safeinputstream.cpp is part of ProcessExecutor.
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

#include "safeinputstream.h"

namespace ProcessExecutor {

SafeInputStream::SafeInputStream(SafeStream &stream): stream(stream) {
}

SafeInputStream::~SafeInputStream() {
}

bool SafeInputStream::isOpen(){
	return stream.isOpen();
}

bool SafeInputStream::operator>>(std::string &text){
	return stream >> text;
}
int SafeInputStream::operator>>=(std::string &text){
	return stream >>= text;
}
} /* namespace ProcessExecutor */
