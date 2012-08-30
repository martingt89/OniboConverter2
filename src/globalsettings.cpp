/*
 * globalsettings.cpp
 *
 *  Created on: 24.8.2012
 *      Author: martint
 */

/**
 * REWRITE, this is only temporary solution
 */

#include "globalsettings.h"
#include <glibmm/miscutils.h>
#include "Xml/settingsloader.h"

GlobalSettings* GlobalSettings::instance = 0;
static const std::string CONFIG_FOLDER_NAME = "oniboconverter2";
static const std::string PROFILES_FOLDER_NAME = "profiles";
static const std::string USER_SETTINGS_FILE = "settings.xml";

GlobalSettings* GlobalSettings::getInstance(){
	if(instance == 0){
		instance = new GlobalSettings();
	}
	return instance;
}

GlobalSettings::GlobalSettings() {
	ffpresetFolder = Path("ffpresets");
	xmlConfigFilePath = Path("data/audio_video_settings.xml");
	defaultProfilesPath = Path("data/profiles");
	userConfigDir = Path(Glib::build_filename(Glib::get_user_config_dir (), CONFIG_FOLDER_NAME));
	userConfigDir.create();
	userProfilesPath = Path(Glib::build_filename(userConfigDir.getPath(), PROFILES_FOLDER_NAME));
	userProfilesPath.create();
	userSettingsFile = Path(Glib::build_filename(userConfigDir.getPath(), USER_SETTINGS_FILE));
	Xml::SettingsLoader loader(userSettingsFile);
	if(loader.load()){
		ffmpegPath = loader.getFFConverterPath();
		destinationPath = loader.getDestinationPath();
	}else{
		ffmpegPath = Path("ffmpeg");	//settings file doesn't exist
		destinationPath = Glib::get_home_dir ();
	}
	generator = new Xml::SettingsGenerator(userSettingsFile, ffmpegPath, destinationPath);
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
Path GlobalSettings::getOutputPath(){
	return destinationPath;
}

void GlobalSettings::setFFmpegPath(const Path& ffmpegPath){
	this->ffmpegPath = ffmpegPath;
	generator->setFFpath(ffmpegPath);
	generator->save();
}
Path GlobalSettings::buildPath(const Path& first, const Path& second){
	std::string path = Glib::build_filename(first.getPath(), second.getPath());
	return Path(path);
}
