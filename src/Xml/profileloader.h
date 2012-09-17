/* ---------------------------------------------------------------------------
** Author: Martin Geier
** profileloader.h is part of OniboConverter2.
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

#ifndef PROFILELOADER_H_
#define PROFILELOADER_H_

#include "../CppExtension/path.h"
#include "../Profile/configuration.h"

namespace Xml {

class ProfileLoader {
public:
	ProfileLoader();
	virtual ~ProfileLoader();
	bool load(const Path& profileFilePath, Profile::Configuration& configuration);
};

} /* namespace Xml */
#endif /* PROFILELOADER_H_ */
