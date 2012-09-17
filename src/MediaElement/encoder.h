/* ---------------------------------------------------------------------------
** Author: Martin Geier
** encoder.h is part of OniboConverter2.
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

#ifndef ENCODER_H_
#define ENCODER_H_

#include <string>
#include <map>
#include "bitrate.h"
#include "ffpreset.h"
#include "../CppExtension/hashmap.h"

namespace MediaElement {

class Encoder {
public:
	enum Type{
		AUDIO, VIDEO
	};
public:
	Encoder();
	Encoder(std::string name, std::string description, bool isEnableMultithread = false);

	std::string getName() const;
	std::string getDescription() const;
	std::string readableForm() const;
	bool operator<(const Encoder& second) const;
	bool operator==(const Encoder& second) const;
	std::list<std::string> getArguments(Encoder::Type encoderType,
			bool enableThreading, int numOfThreads) const;
	bool isSupportedThreading() const;
private:
	std::string name;
	std::string description;
	bool enableMultithread;
};

class Encoders{
public:
	void addEncoder(const Encoder& encoder);
	std::list<Encoder> getEncoders() const;
	Encoder getEncoderByName(const std::string& encoderName) const;
	bool getEncoderByName(const std::string& encoderName, Encoder& encoder) const;
private:
	CppExtension::HashMap<std::string, Encoder> encoders;
};

} /* namespace MediaElement */
#endif /* ENCODER_H_ */
