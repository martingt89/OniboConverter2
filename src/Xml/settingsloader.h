/*
 * settingsloader.h
 *
 *  Created on: 30.8.2012
 *      Author: martint
 */

#ifndef SETTINGSLOADER_H_
#define SETTINGSLOADER_H_

#include "../CppExtension/path.h"
#include "../CppExtension/hashmap.h"
#include "../userpreferences.h"

namespace Xml {

class SettingsLoader{
public:
	SettingsLoader(const Path& settingsFilePath);
	virtual ~SettingsLoader();
	bool load(CppExtension::HashMap<UserPreferences::UserPreferencesOpt, std::string>& optToValue);
private:
	Path settingsFilePath;
};

} /* namespace Xml */
#endif /* SETTINGSLOADER_H_ */
