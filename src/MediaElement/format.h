/* ---------------------------------------------------------------------------
** Author: Martin Geier
** format.h is part of OniboConverter2.
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

#ifndef FORMAT_H_
#define FORMAT_H_

#include "encoder.h"
#include "../CppExtension/hashmap.h"

namespace MediaElement {

class Format {
public:
	enum FormatType{
		FORMAT_TYPE_AUDIO, FORMAT_TYPE_VIDEO
	};
public:
	Format();
	Format(std::string name, FormatType formatType);
	std::string getName() const;
	std::string readableForm() const;
	FormatType getFormatType() const;
	bool operator<(const Format& second) const;
	bool operator==(const Format& second) const;
private:
	std::string name;
	FormatType formatType;
};

class Formats{
public:
	void addFormat(const Format& format);
	std::list<Format> getVideoFormatsList() const;
	std::list<Format> getAudioFormatsList() const;
	std::list<Format> getFormatsList() const;
	Format getFormatByName(std::string formatName) const;
	bool getFormatByName(std::string formatName, const Format::FormatType& type, Format& format) const;
	bool isAudioOnly() const;

private:
	CppExtension::HashMap<std::string, Format> videoFormats;
	CppExtension::HashMap<std::string, Format> audioFormats;
};

} /* namespace MediaElement */
#endif /* FORMAT_H_ */
