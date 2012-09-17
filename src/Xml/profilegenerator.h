/* ---------------------------------------------------------------------------
** Author: Martin Geier
** profilegenerator.h is part of OniboConverter2.
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

#ifndef PROFILEGENERATOR_H_
#define PROFILEGENERATOR_H_

#include <vector>
#include "xmlgenerator.h"
#include "../Profile/configuration.h"

namespace Xml {

class ProfileGenerator {
public:
	ProfileGenerator(const Path& outputDirectory);
	virtual ~ProfileGenerator();
	void generateFile(const Profile::Configuration& profile);
private:
	std::vector<PathNode> toPathVector(std::list<std::string> list, std::string value);
	const Path outputDirectory;
};

} /* namespace Xml */
#endif /* PROFILEGENERATOR_H_ */
