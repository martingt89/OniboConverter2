/*
 * settingsgenerator.h
 *
 *  Created on: 30.8.2012
 *      Author: martint
 */

#ifndef SETTINGSGENERATOR_H_
#define SETTINGSGENERATOR_H_

#include "xmlgenerator.h"
#include "../CppExtension/path.h"
#include "../CppExtension/hashmap.h"
#include "../userpreferences.h"

namespace Xml {

class SettingsGenerator {
public:
	SettingsGenerator(const Path& destination);
	virtual ~SettingsGenerator();
	void setFFpath(const Path& ffmpegPath);
	void setDestination(const Path& destination);
	void save(CppExtension::HashMap<UserPreferences::UserPreferencesOpt, std::string> optToValue);
private:
	std::vector<PathNode> toPathVector(std::list<std::string> list, std::string value);
	Path settingsFile;
};

} /* namespace Xml */
#endif /* SETTINGSGENERATOR_H_ */
