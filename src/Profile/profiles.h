/*
 * profiles.h
 *
 *  Created on: 8.9.2012
 *      Author: martin
 */

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
