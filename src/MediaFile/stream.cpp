/* ---------------------------------------------------------------------------
** Author: Martin Geier
** stream.cpp is part of OniboConverter2.
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

#include "stream.h"

namespace MediaFile {

Stream::Stream(int firstNumber, int secondNumebr, std::string name) :
		streamNumber(firstNumber, secondNumebr), name(name) {
}

Stream::~Stream() {}

std::pair<int, int> Stream::getStreamNumber() const{
	return streamNumber;
}
std::string Stream::getStreamName() const{
	return name;
}
} /* namespace MediaFile */
