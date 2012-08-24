/*
 * globalsettings.h
 *
 *  Created on: 24.8.2012
 *      Author: martint
 */

#ifndef GLOBALSETTINGS_H_
#define GLOBALSETTINGS_H_

#include "CppExtension/path.h"

class GlobalSettings {
public:
	static GlobalSettings* getInstance();
	virtual ~GlobalSettings();
	Path getFFpresetFolder();
	Path getFFmpegPath();
	Path getXmlConfigFilePath();
	Path getDefaultProfilesPath();
	Path getUserProfilesPath();

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
	Path userConfigFile;
};

#endif /* GLOBALSETTINGS_H_ */
