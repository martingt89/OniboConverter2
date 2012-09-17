/* ---------------------------------------------------------------------------
** Author: Martin Geier
** audiograde.cpp is part of OniboConverter2.
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

#include "audiograde.h"

#include "../helper.h"

namespace MediaElement {

const static std::string DEFAULT = "-- default --";

AudioGrade::AudioGrade() {
	type = BITRATE_TYPE;
	value = -1;
}

AudioGrade::~AudioGrade() {}

AudioGrade::AudioGrade(int value, Type type){
	this->type = type;
	this->value = value;
}
int AudioGrade::getValue() const{
	return value;
}
bool AudioGrade::operator== (const AudioGrade& second) const{
	return this->value == second.value;
}
std::string AudioGrade::readableForm() const{
	if(this->isDefault()){
		return DEFAULT;
	}
	return toS(value);
}
AudioGrade::Type AudioGrade::getType() const{
	return type;
}

bool AudioGrade::isDefault() const{
	return value < 0;
}

} /* namespace MediaElement */
