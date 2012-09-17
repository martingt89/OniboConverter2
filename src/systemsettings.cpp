/* ---------------------------------------------------------------------------
** Author: Martin Geier
** OniboConverter2.cpp is part of OniboConverter2.
**
** RegexTools is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
** -------------------------------------------------------------------------*/
#include "systemsettings.h"
#include <glibmm/miscutils.h>
#include "Xml/settingsloader.h"

SystemSettings* SystemSettings::instance = 0;
static const std::string CONFIG_FOLDER_NAME = "oniboconverter2";
static const std::string PROFILES_FOLDER_NAME = "profiles";
static const std::string USER_SETTINGS_FILE = "settings.xml";

#ifdef PROGDIR
static const std::string INSTALL_PATH = Path(DATADIR, PROGDIR).getPath();
#else
static const std::string INSTALL_PATH = "data";
#endif

SystemSettings* SystemSettings::getInstance(){
	if(instance == 0){
		instance = new SystemSettings();
	}
	return instance;
}

SystemSettings::SystemSettings() {
	ffpresetFolder = Path(INSTALL_PATH, "ffpresets");
	xmlConfigFilePath = Path(INSTALL_PATH, "audio_video_settings.xml");
	defaultProfilesPath = Path(INSTALL_PATH, "profiles");
	gladeFilesFolder = Path(INSTALL_PATH);
	userConfigDir = Path(Glib::get_user_config_dir (), CONFIG_FOLDER_NAME);
	userConfigDir.create();
	userProfilesPath = Path(userConfigDir.getPath(), PROFILES_FOLDER_NAME);
	userProfilesPath.create();
	userSettingsFile = Path(userConfigDir.getPath(), USER_SETTINGS_FILE);
}

SystemSettings::~SystemSettings() {}

Path SystemSettings::getFFpresetFolder(){
	return ffpresetFolder;
}
Path SystemSettings::getXmlConfigFilePath(){
	return xmlConfigFilePath;
}
Path SystemSettings::getDefaultProfilesPath(){
	return defaultProfilesPath;
}
Path SystemSettings::getUserProfilesPath(){
	return userProfilesPath;
}
Path SystemSettings::getUserSettingsFile(){
	return userSettingsFile;
}
Path SystemSettings::getGladeFilesFolder(){
	return gladeFilesFolder;
}
