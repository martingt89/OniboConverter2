/*
 * profilegenerator.h
 *
 *  Created on: 2.9.2012
 *      Author: martint
 */

#ifndef PROFILEGENERATOR_H_
#define PROFILEGENERATOR_H_

#include <vector>
#include "xmlgenerator.h"
#include "../Profile/profile.h"

namespace Xml {

class ProfileGenerator {
public:
	ProfileGenerator(const Path& outputDirectory);
	virtual ~ProfileGenerator();
	void generateFile(const Profile::Profile& profile);
private:
	std::vector<PathNode> toPathVector(std::list<std::string> list, std::string value);
	const Path outputDirectory;
};

} /* namespace Xml */
#endif /* PROFILEGENERATOR_H_ */
