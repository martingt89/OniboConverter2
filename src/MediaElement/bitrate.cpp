/* ---------------------------------------------------------------------------
** Author: Martin Geier
** bitrate.cpp is part of OniboConverter2.
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

#include "bitrate.h"
#include "../helper.h"

namespace MediaElement {

Bitrate::Bitrate(){
	this->value = 0;
	minBitrate = -1;
	maxBitrate = -1;
}
Bitrate::Bitrate(int bitrate, int minBitrate, int maxBitrate) {
	this->value = bitrate;
	this->minBitrate = minBitrate;
	this->maxBitrate = maxBitrate;
}
int Bitrate::getMinBitrate() const{
	return minBitrate;
}
int Bitrate::getMaxBitrate() const{
	return maxBitrate;
}
std::string Bitrate::readableForm() const{
	std::string min = " -";
	if(minBitrate >= 0){
		min = " "+toS(minBitrate);
	}
	std::string max = " -";
	if(maxBitrate >= 0){
		max = " "+toS(maxBitrate);
	}
	if(maxBitrate >= 0 || minBitrate >= 0){
		return toS(value) + min + max;
	}
	return toS(value);
}
int Bitrate::getValue() const{
	return value;
}
bool Bitrate::operator== (const Bitrate& second) const{
	return (value == second.value) &&
			(minBitrate == second.minBitrate) &&
			(maxBitrate == second.maxBitrate);
}
} /* namespace MediaElement */
