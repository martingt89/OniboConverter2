/* ---------------------------------------------------------------------------
** Author: Martin Geier
** audiostream.h is part of OniboConverter2.
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

#ifndef AUDIOSTREAM_H_
#define AUDIOSTREAM_H_

#include <string>
#include "stream.h"
#include "../CppExtension/hashmap.h"

namespace MediaFile {

class AudioStream : public Stream{
public:
	enum Audio{
		CODEC, BITRATE, SAMPLERATE, CHANNELS
	};
public:
	AudioStream(int firstNumber, int secondNumber, std::string name = std::string());
	virtual ~AudioStream();
	void setValue(const Audio& name, const std::string& value);
	bool getValue(const Audio& name, std::string& value) const;
private:
	CppExtension::HashMap<Audio, std::string> content;
};

} /* namespace MediaFile */
#endif /* AUDIOSTREAM_H_ */
