/* ---------------------------------------------------------------------------
** Author: Martin Geier
** samplerate.h is part of OniboConverter2.
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

#ifndef SAMPLERATE_H_
#define SAMPLERATE_H_

#include <list>
#include <string>

namespace MediaElement {

class Samplerate {
public:
	Samplerate();
	Samplerate(int samplerate);
	int getValue() const;
	std::string readableForm() const;
	bool isOriginal() const;
private:
	int samplerate;
};

class Samplerates{
public:
	void addSamplerate(const Samplerate& samplerate);
	std::list<Samplerate> getSamplerates() const;
private:
	std::list<Samplerate> samplerates;
};

} /* namespace MediaElement */
#endif /* SAMPLERATE_H_ */
