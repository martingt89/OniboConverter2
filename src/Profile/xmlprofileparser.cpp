/*
 * xmlprofileparser.cpp
 *
 *  Created on: 12.8.2012
 *      Author: martint
 */

#include "xmlprofileparser.h"
#include <iostream>		//todo remove
#include <algorithm>
#include "../helper.h"

namespace Profile {

XmlProfileParser::XmlProfileParser() {
	actualProfile = NULL;
	pathToOptions.set(toPath({"profile", "name"}), Profile::NAME_OPT);
	pathToOptions.set(toPath({"profile", "container"}), Profile::CONTAINER_OPT);
	pathToOptions.set(toPath({"profile", "video", "mode"}), Profile::VIDEO_MODE_OPT);
	pathToOptions.set(toPath({"profile", "video", "format"}), Profile::VIDEO_FORMAT_OPT);
	pathToOptions.set(toPath({"profile", "video", "encoder"}), Profile::VIDEO_ENCODER_OPT);
	pathToOptions.set(toPath({"profile", "video", "framerate"}), Profile::VIDEO_FRAMERATE_OPT);
	pathToOptions.set(toPath({"profile", "video", "bitrate", "value"}), Profile::VIDEO_BITRATE_OPT);
	pathToOptions.set(toPath({"profile", "video", "bitrate", "min"}), Profile::VIDEO_BITRATE_MIN_OPT);
	pathToOptions.set(toPath({"profile", "video", "bitrate", "max"}), Profile::VIDEO_BITRATE_MAX_OPT);
	pathToOptions.set(toPath({"profile", "video", "resolution", "x"}), Profile::VIDEO_RESOLUTION_X_OPT);
	pathToOptions.set(toPath({"profile", "video", "resolution", "y"}), Profile::VIDEO_RESOLUTION_Y_OPT);
	pathToOptions.set(toPath({"profile", "video", "resolution", "aspect"}),Profile::VIDEO_RESOLUTION_ASP_OPT);
	pathToOptions.set(toPath({"profile", "video", "resolution", "name"}),Profile::VIDEO_RESOLUTION_NAME_OPT);
	pathToOptions.set(toPath({"profile", "video", "ffpreset", "prefix"}),Profile::VIDEO_FFPRESET_PREFIX_OPT);
	pathToOptions.set(toPath({"profile", "video", "ffpreset", "path"}),Profile::VIDEO_FFPRESET_PATH_OPT);
	pathToOptions.set(toPath({"profile", "video", "ffpreset", "buildin"}),Profile::VIDEO_FFPRESET_BUILDIN_OPT);

	pathToOptions.set(toPath({"profile", "audio", "mode"}),Profile::AUDIO_MODE_OPT);
	pathToOptions.set(toPath({"profile", "audio", "format"}),Profile::AUDIO_FORMAT_OPT);
	pathToOptions.set(toPath({"profile", "audio", "encoder"}),Profile::AUDIO_ENCODER_OPT);
	pathToOptions.set(toPath({"profile", "audio", "bitrate"}),Profile::AUDIO_BITRATE_OPT);
	pathToOptions.set(toPath({"profile", "audio", "samplerate"}),Profile::AUDIO_SAMPLERATE_OPT);
	pathToOptions.set(toPath({"profile", "audio", "channel", "value"}),Profile::AUDIO_CHANNEL_VALUE_OPT);
	pathToOptions.set(toPath({"profile", "audio", "channel", "name"}),Profile::AUDIO_CHANNEL_NAME_OPT);

	pathToOptions.set(
			toPath({"profile", "manualsettings", "setting", "command"}), Profile::MANUAL_COMMAND_OPT);
	pathToOptions.set(toPath({"profile", "manualsettings", "setting", "arg"}), Profile::MANUAL_ARG_OPT);
}

XmlProfileParser::~XmlProfileParser() {}

bool XmlProfileParser::parseFile(const Path& filePath, Profile& profile){
	path.clear();
	actualProfile = &profile;
	try{
		this->parse_file(filePath.getPath());
	}catch(std::exception& ex){
		std::cout<<"Parsovanie sa dojebalo: "<<ex.what()<<std::endl; //todo remove
		actualProfile = NULL;
		return false;
	}
	actualProfile = NULL;
	return true;
}
void XmlProfileParser::on_start_element(const Glib::ustring& name, const AttributeList& attributes){
	path.push_back(name);
}
void XmlProfileParser::on_end_element(const Glib::ustring& name){
	path.pop_back();
}
void XmlProfileParser::on_characters(const Glib::ustring& characters){
	if(actualProfile){
		std::string value = clearString(characters);
		if(value.size() > 0){
			Profile::Options options;
			if(toOptions(path, options)){
				actualProfile->addProperty(options, value);
			}
		}
	}
}
bool XmlProfileParser::toOptions(const std::list<std::string>& path, Profile::Options& options){
	std::string hash = toPath(path);
	bool exist = false;
	options = pathToOptions.get(hash, exist);
//	std::cout<<hash<<" "<<options<<" "<<exist<<std::endl;
	return exist;
}
std::string XmlProfileParser::toPath(const std::initializer_list<std::string>& path){
	std::list<std::string> listPath;
	for (auto x : path){
		listPath.push_back(x);
	}
	return toPath(listPath);
}
std::string XmlProfileParser::toPath(const std::list<std::string>& path){
	std::string result;
	for (auto x : path){
		result = result + "_" + x + "_";
	}
	return result;
}
} /* namespace Profile */
