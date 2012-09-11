/*
 * sysstemsettings.h
 *
 *  Created on: 24.8.2012
 *      Author: martint
 */

#ifndef SYSTEMSETTINGS_H_
#define SYSTEMSETTINGS_H_

#include "CppExtension/path.h"
#include "Xml/settingsgenerator.h"

class SystemSettings {
public:
	static SystemSettings* getInstance();
	virtual ~SystemSettings();
	Path getFFpresetFolder();
	Path getXmlConfigFilePath();
	Path getDefaultProfilesPath();
	Path getUserProfilesPath();
	Path getUserSettingsFile();
private:
	SystemSettings();
	static SystemSettings* instance;
	Path ffpresetFolder;
	Path xmlConfigFilePath;
	Path defaultProfilesPath;
	Path userProfilesPath;
	Path userConfigDir;
	Path userSettingsFile;
};

#endif /* SYSTEMSETTINGS_H_ */
