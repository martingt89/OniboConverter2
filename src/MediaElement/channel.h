/* ---------------------------------------------------------------------------
** Author: Martin Geier
** channel.h is part of OniboConverter2.
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

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <list>
#include <string>

namespace MediaElement {

class Channel {
public:
	Channel();
	Channel(const std::string& name, const int& value);
	virtual ~Channel();
	int getValue() const;
	std::string readableForm() const;
	std::string getName() const;
	bool isOriginal() const;
private:
	std::string name;
	int value;
};

typedef std::list<Channel> Channels;

} /* namespace MediaElement */
#endif /* CHANNEL_H_ */
