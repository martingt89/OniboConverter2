/*
 * xmlfilesdefinitions.cpp
 *
 *  Created on: 7.9.2012
 *      Author: martin
 */

#include "xmlfilesdefinitions.h"

XmlFilesDefinitions* XmlFilesDefinitions::instance = 0;

XmlFilesDefinitions::XmlFilesDefinitions() {
	userPreferences.add(toList( { "settings", "ext_converter_path" }),
			UserPreferences::EXT_CONVERTER_PATH);
	userPreferences.add(toList( { "settings", "output_destination" }),
			UserPreferences::DESTINATION_PATH);
	userPreferences.add(toList( { "settings", "number_of_cpus" }),
			UserPreferences::NUM_OF_CPU);
	userPreferences.add(toList( { "settings", "encoder_multithread" }),
			UserPreferences::ENABLE_MULTITHREAD_FOR_ENC);
	//************************************************************************************************************
	profil.add(toList( { "profile", "name" }), Profile::Profile::NAME_OPT);
	profil.add(toList( { "profile", "container" }),
			Profile::Profile::CONTAINER_OPT);
	profil.add(toList( { "profile", "video", "mode" }),
			Profile::Profile::VIDEO_MODE_OPT);
	profil.add(toList( { "profile", "video", "format" }),
			Profile::Profile::VIDEO_FORMAT_OPT);
	profil.add(toList( { "profile", "video", "encoder" }),
			Profile::Profile::VIDEO_ENCODER_OPT);
	profil.add(toList( { "profile", "video", "framerate" }),
			Profile::Profile::VIDEO_FRAMERATE_OPT);
	profil.add(toList( { "profile", "video", "bitrate", "value" }),
			Profile::Profile::VIDEO_BITRATE_OPT);
	profil.add(toList( { "profile", "video", "bitrate", "min" }),
			Profile::Profile::VIDEO_BITRATE_MIN_OPT);
	profil.add(toList( { "profile", "video", "bitrate", "max" }),
			Profile::Profile::VIDEO_BITRATE_MAX_OPT);
	profil.add(toList( { "profile", "video", "resolution", "x" }),
			Profile::Profile::VIDEO_RESOLUTION_X_OPT);
	profil.add(toList( { "profile", "video", "resolution", "y" }),
			Profile::Profile::VIDEO_RESOLUTION_Y_OPT);
	profil.add(toList( { "profile", "video", "resolution", "aspect" }),
			Profile::Profile::VIDEO_RESOLUTION_ASP_OPT);
	profil.add(toList( { "profile", "video", "resolution", "name" }),
			Profile::Profile::VIDEO_RESOLUTION_NAME_OPT);
	profil.add(toList( { "profile", "video", "ffpreset", "prefix" }),
			Profile::Profile::VIDEO_FFPRESET_PREFIX_OPT);
	profil.add(toList( { "profile", "video", "ffpreset", "path" }),
			Profile::Profile::VIDEO_FFPRESET_PATH_OPT);
	profil.add(toList( { "profile", "video", "ffpreset", "type" }),
			Profile::Profile::VIDEO_FFPRESET_TYPE_OPT);
	//---------------------------------------------------------------
	profil.add(toList( { "profile", "audio", "mode" }),
			Profile::Profile::AUDIO_MODE_OPT);
	profil.add(toList( { "profile", "audio", "format" }),
			Profile::Profile::AUDIO_FORMAT_OPT);
	profil.add(toList( { "profile", "audio", "encoder" }),
			Profile::Profile::AUDIO_ENCODER_OPT);
	profil.add(toList( { "profile", "audio", "bitrate" }),
			Profile::Profile::AUDIO_BITRATE_OPT);
	profil.add(toList( { "profile", "audio", "samplerate" }),
			Profile::Profile::AUDIO_SAMPLERATE_OPT);
	profil.add(toList( { "profile", "audio", "channel", "value" }),
			Profile::Profile::AUDIO_CHANNEL_VALUE_OPT);
	profil.add(toList( { "profile", "audio", "channel", "name" }),
			Profile::Profile::AUDIO_CHANNEL_NAME_OPT);
	//---------------------------------------------------------------
	profil.add(toList( { "profile", "manualsettings", "setting", "command" }),
			Profile::Profile::MANUAL_COMMAND_OPT);
	profil.add(toList( { "profile", "manualsettings", "setting", "arg" }),
			Profile::Profile::MANUAL_ARG_OPT);
	//=====================================================================
}

XmlFilesDefinitions* XmlFilesDefinitions::getInstance(){
	if(instance == 0){
		instance = new XmlFilesDefinitions();
	}
	return instance;
}

Xml::ConvertTable<UserPreferences::UserPreferencesOpt>& XmlFilesDefinitions::getUserPreferencesTable(){
	return userPreferences;
}

Xml::ConvertTable<Profile::Profile::Options>& XmlFilesDefinitions::getProfileTable(){
	return profil;
}
