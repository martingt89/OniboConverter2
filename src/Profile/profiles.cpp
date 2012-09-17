/* ---------------------------------------------------------------------------
** Author: Martin Geier
** profiles.cpp is part of OniboConverter2.
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

#include "profiles.h"
#include "../systemsettings.h"
#include "../Xml/profileloader.h"

namespace Profile {

Profiles::Profiles(const MediaElement::ElementsDB& elementsDb) : elementsDb(elementsDb) {}

Profiles::~Profiles() {}

void Profiles::load(){
	Path predefinedProfiles = SystemSettings::getInstance()->getDefaultProfilesPath();
	loadProfilesInFolder(predefinedProfiles);

	Path userProfiles = SystemSettings::getInstance()->getUserProfilesPath();
	loadProfilesInFolder(userProfiles);
}

std::list<Profile> Profiles::getProfiles() const{
	return profiles;
}

void Profiles::loadProfilesInFolder(const Path& folder) {
	Xml::ProfileLoader loader;
	std::list<Path> files;
	if (folder.getSubfiles(files)) {
		for (auto file : files) {
			Configuration profileConfiguration(elementsDb);
			if (loader.load(file, profileConfiguration)) {
				profiles.push_back(profileConfiguration.getProfile());
			}
		}
	}
}

} /* namespace Profile */
