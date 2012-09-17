/* ---------------------------------------------------------------------------
** Author: Martin Geier
** profiles.h is part of OniboConverter2.
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

#ifndef PROFILES_H_
#define PROFILES_H_

#include <list>
#include "profile.h"
#include "../CppExtension/path.h"
#include "../MediaElement/elementsdb.h"

namespace Profile {

class Profiles {
public:
	Profiles(const MediaElement::ElementsDB& elementsDb);
	virtual ~Profiles();
	void load();
	std::list<Profile> getProfiles() const;
private:
	std::list<Profile> profiles;
	const MediaElement::ElementsDB& elementsDb;
	void loadProfilesInFolder(const Path& folder);
};

} /* namespace Profile */
#endif /* PROFILES_H_ */
