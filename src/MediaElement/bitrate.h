/* ---------------------------------------------------------------------------
** Author: Martin Geier
** bitrate.h is part of OniboConverter2.
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

#ifndef BITRATE_H_
#define BITRATE_H_

#include <list>
#include <string>

namespace MediaElement {

class Bitrate {
public:
	Bitrate();
	Bitrate(int bitrate, int bufferSize, int minBitrate, int maxBitrate);
	int getValue() const;
	int getMinBitrate() const;
	int getMaxBitrate() const;
	int getBufferSize() const;
	bool operator== (const Bitrate& second) const;
	std::string readableForm() const;

private:
	int value;
	int minBitrate;
	int maxBitrate;
	int bufferSize;
};

typedef std::list<Bitrate> Bitrates;

} /* namespace MediaElement */
#endif /* BITRATE_H_ */
