/*
 * profiles.cpp
 *
 *  Created on: 8.9.2012
 *      Author: martin
 */

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
