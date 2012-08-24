/*
 * globalsettings.cpp
 *
 *  Created on: 24.8.2012
 *      Author: martint
 */

#include "globalsettings.h"
#include <glibmm/miscutils.h>

GlobalSettings* GlobalSettings::instance = 0;
static const std::string CONFIG_FOLDER_NAME = "oniboconverter2";
static const std::string PROFILES_FOLDER_NAME = "profiles";
static const std::string CONFIG_FILE_NAME = "config.xml";

GlobalSettings* GlobalSettings::getInstance(){
	if(instance == 0){
		instance = new GlobalSettings();
	}
	return instance;
}

GlobalSettings::GlobalSettings() {
	//todo create folders	!!!
	ffpresetFolder = Path("ffpresets");
	xmlConfigFilePath = Path("data/audio_video_settings.xml");
	defaultProfilesPath = Path("data/profiles");
	userConfigDir = Path(Glib::build_filename(Glib::get_user_config_dir (), CONFIG_FOLDER_NAME));
	userProfilesPath = Path(Glib::build_filename(userConfigDir.getPath(), PROFILES_FOLDER_NAME));
	userConfigFile = Path(Glib::build_filename(userConfigDir.getPath(), CONFIG_FILE_NAME));
	//todo create file tree
	//todo load ffmpeg path
	ffmpegPath = Path("ffmpeg");	//todo fake
}

GlobalSettings::~GlobalSettings() {}

Path GlobalSettings::getFFmpegPath(){
	return ffmpegPath;
}
Path GlobalSettings::getFFpresetFolder(){
	return ffpresetFolder;
}
Path GlobalSettings::getXmlConfigFilePath(){
	return xmlConfigFilePath;
}
Path GlobalSettings::getDefaultProfilesPath(){
	return defaultProfilesPath;
}
Path GlobalSettings::getUserProfilesPath(){
	return userProfilesPath;
}

void GlobalSettings::setFFmpegPath(const Path& ffmpegPath){
	this->ffmpegPath = ffmpegPath;
}
Path GlobalSettings::buildPath(const Path& first, const Path& second){
	std::string path = Glib::build_filename(first.getPath(), second.getPath());
	return Path(path);
}
