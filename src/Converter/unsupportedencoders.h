/* ---------------------------------------------------------------------------
** Author: Martin Geier
** unsupportedencoders.h is part of OniboConverter2.
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

#ifndef UNSUPPORTEDENCODERS_H_
#define UNSUPPORTEDENCODERS_H_

#include <string>
#include <list>
namespace Converter {

class UnsupportedEncoders {
public:
	enum PriorityLevel{
		BEGIN = 1, MEDIUM = 1, HIGHT = 2, END = 3
	};
	void addUnsupportedEncoder(const std::string &name, const std::string &description, PriorityLevel level);
	bool isEmpty();
	std::list<std::pair<std::string, UnsupportedEncoders::PriorityLevel> > getEncoders() const;
private:
	std::list<std::pair<std::string, PriorityLevel> > encoders;
};

} /* namespace Converter */
#endif /* UNSUPPORTEDENCODERS_H_ */
