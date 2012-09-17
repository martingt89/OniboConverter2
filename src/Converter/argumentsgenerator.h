/* ---------------------------------------------------------------------------
** Author: Martin Geier
** argumentsgenerator.h is part of OniboConverter2.
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

#ifndef ARGUMENTSGENERATOR_H_
#define ARGUMENTSGENERATOR_H_

#include <list>
#include "../Profile/profile.h"

namespace Converter {

class ArgumentsGenerator {
public:
	ArgumentsGenerator();
	void setThreading(const bool& enableFileThreading, const int& numOfThreads);
	void setProfile(const Profile::Profile& actualProfile);
	std::list<std::string> generate();
private:
	void generateVideo(std::list<std::string>& args);
	void generateAudio(std::list<std::string>& args);
	//filters
	Profile::Profile actualProfile;
	bool isFileThreading;
	int numOfThreads;
};

} /* namespace Converter */
#endif /* ARGUMENTSGENERATOR_H_ */
