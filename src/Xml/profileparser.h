/*
 * profileparser.h
 *
 *  Created on: 7.9.2012
 *      Author: martin
 */

#ifndef PROFILEPARSER_H_
#define PROFILEPARSER_H_

#include "../CppExtension/path.h"
#include "../Profile/profile.h"

namespace Xml {

class ProfileParser {
public:
	ProfileParser();
	virtual ~ProfileParser();
	bool load(const Path& profileFilePath, Profile::Profile& profile);
};

} /* namespace Xml */
#endif /* PROFILEPARSER_H_ */
