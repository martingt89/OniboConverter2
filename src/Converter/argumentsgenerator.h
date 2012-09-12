/*
 * argumentsgenerator.h
 *
 *  Created on: 10.9.2012
 *      Author: martin
 */

#ifndef ARGUMENTSGENERATOR_H_
#define ARGUMENTSGENERATOR_H_

#include <list>
#include "../Profile/profile.h"

namespace Converter {

class ArgumentsGenerator {
public:
	ArgumentsGenerator();
	void setThreading(const bool& enableFileThreading, const int& numOfThreads);
	void setProfile(const Profile::Profile& actualProfile);
	std::list<std::string> generate();
private:
	void generateVideo(std::list<std::string>& args);
	void generateAudio(std::list<std::string>& args);
	//filters
	Profile::Profile actualProfile;
	bool isFileThreading;
	int numOfThreads;
};

} /* namespace Converter */
#endif /* ARGUMENTSGENERATOR_H_ */
