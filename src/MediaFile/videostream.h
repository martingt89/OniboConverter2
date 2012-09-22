/* ---------------------------------------------------------------------------
** Author: Martin Geier
** videostream.h is part of OniboConverter2.
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

#ifndef VIDEOSTREAM_H_
#define VIDEOSTREAM_H_

#include <string>
#include "stream.h"
#include "../CppExtension/hashmap.h"

namespace MediaFile {

class VideoStream : public Stream {
public:
	VideoStream(int firstNumber, int secondNumber, std::string id, std::string language = std::string());
	enum Video{
			CODEC, COLORSPACE, RESX, RESY, TBR, TBN, TBC, FPS
	};
public:
	void setValue(const Video& name, const std::string& value);
	bool getValue(const Video& name, std::string& value) const;
	void setStream(int f, int r);
	int priority() const;
private:
	CppExtension::HashMap<Video, std::string> content;
};

} /* namespace MediaFile */
#endif /* VIDEOSTREAM_H_ */
