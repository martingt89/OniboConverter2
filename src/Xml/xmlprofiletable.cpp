/*
 * xmlprofiletable.cpp
 *
 *  Created on: 24.8.2012
 *      Author: martint
 */

#include "xmlprofiletable.h"

namespace Xml {

XmlProfileTable::XmlProfileTable() {
	add(toList({"profile", "name"}),
			Profile::Profile::NAME_OPT);
	add(toList({"profile", "container"}),
			Profile::Profile::CONTAINER_OPT);
	add(toList({"profile", "video", "mode"}),
			Profile::Profile::VIDEO_MODE_OPT);
	add(toList({"profile", "video", "format"}),
			Profile::Profile::VIDEO_FORMAT_OPT);
	add(toList({"profile", "video", "encoder"}),
			Profile::Profile::VIDEO_ENCODER_OPT);
	add(toList({"profile", "video", "framerate"}),
			Profile::Profile::VIDEO_FRAMERATE_OPT);
	add(toList({"profile", "video", "bitrate", "value"}),
			Profile::Profile::VIDEO_BITRATE_OPT);
	add(toList({"profile", "video", "bitrate", "min"}),
			Profile::Profile::VIDEO_BITRATE_MIN_OPT);
	add(toList({"profile", "video", "bitrate", "max"}),
			Profile::Profile::VIDEO_BITRATE_MAX_OPT);
	add(toList({"profile", "video", "resolution", "x"}),
			Profile::Profile::VIDEO_RESOLUTION_X_OPT);
	add(toList({"profile", "video", "resolution", "y"}),
			Profile::Profile::VIDEO_RESOLUTION_Y_OPT);
	add(toList({"profile", "video", "resolution", "aspect"}),
			Profile::Profile::VIDEO_RESOLUTION_ASP_OPT);
	add(toList({"profile", "video", "resolution", "name"}),
			Profile::Profile::VIDEO_RESOLUTION_NAME_OPT);
	add(toList({"profile", "video", "ffpreset", "prefix"}),
			Profile::Profile::VIDEO_FFPRESET_PREFIX_OPT);
	add(toList({"profile", "video", "ffpreset", "path"}),
			Profile::Profile::VIDEO_FFPRESET_PATH_OPT);
	add(toList({"profile", "video", "ffpreset", "type"}),
			Profile::Profile::VIDEO_FFPRESET_TYPE_OPT);
//---------------------------------------------------------------
	add(toList({"profile", "audio", "mode"}),
			Profile::Profile::AUDIO_MODE_OPT);
	add(toList({"profile", "audio", "format"}),
			Profile::Profile::AUDIO_FORMAT_OPT);
	add(toList({"profile", "audio", "encoder"}),
			Profile::Profile::AUDIO_ENCODER_OPT);
	add(toList({"profile", "audio", "bitrate"}),
			Profile::Profile::AUDIO_BITRATE_OPT);
	add(toList({"profile", "audio", "samplerate"}),
			Profile::Profile::AUDIO_SAMPLERATE_OPT);
	add(toList({"profile", "audio", "channel", "value"}),
			Profile::Profile::AUDIO_CHANNEL_VALUE_OPT);
	add(toList({"profile", "audio", "channel", "name"}),
			Profile::Profile::AUDIO_CHANNEL_NAME_OPT);
//---------------------------------------------------------------
	add(toList({"profile", "manualsettings", "setting", "command"}),
			Profile::Profile::MANUAL_COMMAND_OPT);
	add(toList({"profile", "manualsettings", "setting", "arg"}),
			Profile::Profile::MANUAL_ARG_OPT);
//=====================================================================
}

XmlProfileTable::~XmlProfileTable() {}

Profile::Profile::Options XmlProfileTable::getOptionsFromList(const std::list<std::string>& list){
	bool exist = false;
	auto options = listToOptions.get(list, exist);
	if(exist){
		return options;
	}
	return Profile::Profile::UNKNOWN_OPT;
}

std::list<std::string> XmlProfileTable::getListFromOptions(const Profile::Profile::Options& options){
	return optionsToList.get(options);
}

void XmlProfileTable::add(const std::list<std::string>& list, const Profile::Profile::Options& options){
	listToOptions.set(list, options);
	optionsToList.set(options, list);
}

std::list<std::string> XmlProfileTable::toList(const std::initializer_list<std::string>& path){
	std::list<std::string> listPath;
	for (const std::string& x : path){
		listPath.push_back(x);
	}
	return listPath;
}

} /* namespace Xml */
