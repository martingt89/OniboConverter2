/* ---------------------------------------------------------------------------
** Author: Martin Geier
** videostream.cpp is part of OniboConverter2.
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

#include "videostream.h"
#include "../helper.h"

namespace MediaFile {

VideoStream::VideoStream(int firstNumber, int secondNumber, std::string id, std::string language) :
		Stream(firstNumber,secondNumber, id, language){}

void VideoStream::setValue(const Video& name, const std::string& value){
	content.set(name, value);
}

int VideoStream::priority() const{
	int resx = toN(content.get(VideoStream::RESX), int());
	int resy = toN(content.get(VideoStream::RESY), int());
	return resx*resx + resy*resy;	//compare slant
}

bool VideoStream::getValue(const Video& name, std::string& value) const{
	bool isExistParameter = false;
	value = content.get(name, isExistParameter);
	return isExistParameter;
}

} /* namespace MediaFile */
