/* ---------------------------------------------------------------------------
** Author: Martin Geier
** convertparser.h is part of OniboConverter2.
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

#ifndef CONVERTPARSER_H_
#define CONVERTPARSER_H_

#include <string>
#include <list>
#include "../RegexTools/regextools.h"

namespace Converter {

class ConvertParser {
public:
	ConvertParser(const double& duration);
	virtual ~ConvertParser();
	bool processLine(const std::string& line, double& fraction, int& remainingTime);
private:
	void addRecord(double diff, double elapsed);
	double getNumSecPerSec();
	double toSecondTime(const std::string& time);
	double aktualTime;
	double duration;
	RegexTools::Regex colonTimeFormat;
	long lastWorldTime;
	std::list<std::pair<double, double> > diffAndTime;
};

} /* namespace Converter */
#endif /* CONVERTPARSER_H_ */
