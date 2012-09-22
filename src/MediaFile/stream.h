/* ---------------------------------------------------------------------------
** Author: Martin Geier
** stream.h is part of OniboConverter2.
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

#ifndef STREAM_H_
#define STREAM_H_

#include <utility>
#include <string>

namespace MediaFile {

class Stream {
public:
	Stream(int firstNumber, int secondNumebr, std::string id, std::string name);
	virtual ~Stream();
	std::pair<int, int> getStreamNumber() const;
	std::string getStreamLanguage() const;
	std::string getStreamId() const;
	bool isDefault() const;
	void setDefault(bool isDefault);
	void setCenvertable(bool convertable);
	bool isCenvertable() const;
private:
	std::pair<int, int> streamNumber;
	std::string id;
	std::string language;
	bool isDef;
	bool convertable;

};

} /* namespace MediaFile */
#endif /* STREAM_H_ */
