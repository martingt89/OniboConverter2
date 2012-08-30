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
	Path getFFmpegPath();
	Path getXmlConfigFilePath();
	Path getDefaultProfilesPath();
	Path getUserProfilesPath();
	Path getOutputPath();

	void setFFmpegPath(const Path& ffmpegPath);
	static Path buildPath(const Path& first, const Path& second);
private:
	GlobalSettings();
	static GlobalSettings* instance;
	Path ffpresetFolder;
	Path ffmpegPath;
	Path xmlConfigFilePath;
	Path defaultProfilesPath;
	Path userProfilesPath;
	Path userConfigDir;
	Path userSettingsFile;
	Path destinationPath;
	Xml::SettingsGenerator* generator;
};

#endif /* GLOBALSETTINGS_H_ */
