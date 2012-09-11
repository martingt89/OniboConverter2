/*
 * sysstemsettings.cpp
 *
 *  Created on: 24.8.2012
 *      Author: martint
 */

#include "systemsettings.h"
#include <glibmm/miscutils.h>
#include "Xml/settingsloader.h"

SystemSettings* SystemSettings::instance = 0;
static const std::string CONFIG_FOLDER_NAME = "oniboconverter2";
static const std::string PROFILES_FOLDER_NAME = "profiles";
static const std::string USER_SETTINGS_FILE = "settings.xml";

SystemSettings* SystemSettings::getInstance(){
	if(instance == 0){
		instance = new SystemSettings();
	}
	return instance;
}

SystemSettings::SystemSettings() {
	ffpresetFolder = Path("ffpresets");
	xmlConfigFilePath = Path("data/audio_video_settings.xml");
	defaultProfilesPath = Path("data/profiles");
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
