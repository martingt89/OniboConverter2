/* ---------------------------------------------------------------------------
** Author: Martin Geier
** xmlfilesdefinitions.cpp is part of OniboConverter2.
**
** OniboConverter2 is free software: you can redistribute it and/or modify
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
	userPreferences.add(toList( { "settings", "disable_show_unenc" }),
				UserPreferences::DISABLE_SHOW_UNENCODER);
	//************************************************************************************************************
	profilConfiguration.add(toList( { "profile", "name" }), Profile::Configuration::NAME_OPT);
	profilConfiguration.add(toList( { "profile", "container"}), Profile::Configuration::CONTAINER_OPT);
	profilConfiguration.add(toList( { "profile", "video", "mode" }),
			Profile::Configuration::VIDEO_MODE_OPT);
	profilConfiguration.add(toList( { "profile", "video", "format" }),
			Profile::Configuration::VIDEO_FORMAT_OPT);
	profilConfiguration.add(toList( { "profile", "video", "encoder" }),
			Profile::Configuration::VIDEO_ENCODER_OPT);
	profilConfiguration.add(toList( { "profile", "video", "framerate" }),
			Profile::Configuration::VIDEO_FRAMERATE_OPT);
	profilConfiguration.add(toList( { "profile", "video", "bitrate", "value" }),
			Profile::Configuration::VIDEO_BITRATE_OPT);
	profilConfiguration.add(toList( { "profile", "video", "bitrate", "min" }),
			Profile::Configuration::VIDEO_BITRATE_MIN_OPT);
	profilConfiguration.add(toList( { "profile", "video", "bitrate", "max" }),
			Profile::Configuration::VIDEO_BITRATE_MAX_OPT);
	profilConfiguration.add(toList( { "profile", "video", "buffer"}),
			Profile::Configuration::VIDEO_BUFFER_OPT);
	profilConfiguration.add(toList( { "profile", "video", "resolution", "x" }),
			Profile::Configuration::VIDEO_RESOLUTION_X_OPT);
	profilConfiguration.add(toList( { "profile", "video", "resolution", "y" }),
			Profile::Configuration::VIDEO_RESOLUTION_Y_OPT);
	profilConfiguration.add(toList( { "profile", "video", "resolution", "aspect" }),
			Profile::Configuration::VIDEO_RESOLUTION_ASP_OPT);
	profilConfiguration.add(toList( { "profile", "video", "resolution", "name" }),
			Profile::Configuration::VIDEO_RESOLUTION_NAME_OPT);
	profilConfiguration.add(toList( { "profile", "video", "ffpreset", "prefix" }),
			Profile::Configuration::VIDEO_FFPRESET_PREFIX_OPT);
	profilConfiguration.add(toList( { "profile", "video", "ffpreset", "path" }),
			Profile::Configuration::VIDEO_FFPRESET_PATH_OPT);
	profilConfiguration.add(toList( { "profile", "video", "ffpreset", "type" }),
			Profile::Configuration::VIDEO_FFPRESET_TYPE_OPT);
	//---------------------------------------------------------------
	profilConfiguration.add(toList( { "profile", "audio", "mode" }),
			Profile::Configuration::AUDIO_MODE_OPT);
	profilConfiguration.add(toList( { "profile", "audio", "format" }),
			Profile::Configuration::AUDIO_FORMAT_OPT);
	profilConfiguration.add(toList( { "profile", "audio", "encoder" }),
			Profile::Configuration::AUDIO_ENCODER_OPT);
	profilConfiguration.add(toList( { "profile", "audio", "grade", "value"}),
			Profile::Configuration::AUDIO_GRADE_VALUE_OPT);
	profilConfiguration.add(toList( { "profile", "audio", "grade", "type"}),
			Profile::Configuration::AUDIO_GRADE_TYPE_OPT);
	profilConfiguration.add(toList( { "profile", "audio", "samplerate" }),
			Profile::Configuration::AUDIO_SAMPLERATE_OPT);
	profilConfiguration.add(toList( { "profile", "audio", "channel", "value" }),
			Profile::Configuration::AUDIO_CHANNEL_VALUE_OPT);
	profilConfiguration.add(toList( { "profile", "audio", "channel", "name" }),
			Profile::Configuration::AUDIO_CHANNEL_NAME_OPT);
	//---------------------------------------------------------------
	profilConfiguration.add(toList( { "profile", "manualsettings", "setting", "command" }),
			Profile::Configuration::MANUAL_COMMAND_OPT);
	profilConfiguration.add(toList( { "profile", "manualsettings", "setting", "arg" }),
			Profile::Configuration::MANUAL_ARG_OPT);
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

Xml::ConvertTable<Profile::Configuration::Options>& XmlFilesDefinitions::getConfigurationTable(){
	return profilConfiguration;
}
