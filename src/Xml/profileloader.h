/*
 * profileloader.h
 *
 *  Created on: 7.9.2012
 *      Author: martin
 */

#ifndef PROFILELOADER_H_
#define PROFILELOADER_H_

#include "../CppExtension/path.h"
#include "../Profile/profile.h"

namespace Xml {

class ProfileLoader {
public:
	ProfileLoader();
	virtual ~ProfileLoader();
	bool load(const Path& profileFilePath, Profile::Profile& profile);
};

} /* namespace Xml */
#endif /* PROFILELOADER_H_ */
