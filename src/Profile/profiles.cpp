/*
 * profiles.cpp
 *
 *  Created on: 8.9.2012
 *      Author: martin
 */

#include "profiles.h"
#include "../globalsettings.h"
#include "../Xml/profileloader.h"

namespace Profile {

Profiles::Profiles() {}

Profiles::~Profiles() {}

void Profiles::load(){
	Path predefinedProfiles = GlobalSettings::getInstance()->getDefaultProfilesPath();
	loadProfilesInFolder(predefinedProfiles);

	Path userProfiles = GlobalSettings::getInstance()->getUserProfilesPath();
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
			Profile profile;
			if (loader.load(file, profile)) {
				profiles.push_back(profile);
			}
		}
	}
}

} /* namespace Profile */
