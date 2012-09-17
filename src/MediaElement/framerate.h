/* ---------------------------------------------------------------------------
** Author: Martin Geier
** framerate.h is part of OniboConverter2.
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

#ifndef FRAMERATE_H_
#define FRAMERATE_H_

#include <list>
#include <string>

namespace MediaElement {

class Framerate {
public:
	Framerate(){framerate = 0;};
	Framerate(double framerate);
	double getValue() const;
	std::string readableForm() const;
	bool isOriginal() const;
private:
	double framerate;
};

class Framerates{
public:
	void addFramerate(const Framerate& framerate);
	std::list<Framerate> getFramerats() const;
private:
	std::list<Framerate> framerates;
};

} /* namespace MediaElement */
#endif /* FRAMERATE_H_ */
