/* ---------------------------------------------------------------------------
** Author: Martin Geier
** audiograde.h is part of OniboConverter2.
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

#ifndef AUDIOGRADE_H_
#define AUDIOGRADE_H_

#include <list>
#include <string>

namespace MediaElement {

class AudioGrade {
public:
	enum Type{
		BITRATE_TYPE, QUALITY_TYPE
	};
	AudioGrade();
	virtual ~AudioGrade();

	AudioGrade(int value, Type type);
	int getValue() const;
	bool operator== (const AudioGrade& second) const;
	std::string readableForm() const;
	Type getType() const;
	bool isDefault() const;
private:
	int value;
	Type type;
};

typedef std::list<AudioGrade> AudioGrades;

} /* namespace MediaElement */
#endif /* AUDIOGRADE_H_ */
