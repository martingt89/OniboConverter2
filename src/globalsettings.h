/*
 * globalsettings.h
 *
 *  Created on: 24.8.2012
 *      Author: martint
 */

#ifndef GLOBALSETTINGS_H_
#define GLOBALSETTINGS_H_

#include "CppExtension/path.h"
#include "Xml/settingsgenerator.h"

class GlobalSettings {
public:
	static GlobalSettings* getInstance();
	virtual ~GlobalSettings();
	Path getFFpresetFolder();
	Path getXmlConfigFilePath();
	Path getDefaultProfilesPath();
	Path getUserProfilesPath();
	Path getUserSettingsFile();
private:
	GlobalSettings();
	static GlobalSettings* instance;
	Path ffpresetFolder;
	Path xmlConfigFilePath;
	Path defaultProfilesPath;
	Path userProfilesPath;
	Path userConfigDir;
	Path userSettingsFile;
};

#endif /* GLOBALSETTINGS_H_ */
