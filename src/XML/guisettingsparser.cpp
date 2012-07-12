/*
 * guisettingsparser.cpp
 *
 *  Created on: 4.7.2012
 *      Author: martint
 */

#include "guisettingsparser.h"
#include "../Tools/settings.h"
#include <iostream> //todo remove

namespace XML {

void GuiSettingsParser::initConvertTable() {
	convertTable["video"] = VIDEO;
	convertTable["gui_settings"] = DOCUMENT;
	convertTable["resolutions"] = RESOLUTIONS;
	convertTable["resolution"] = RESOLUTION;
	convertTable["bitrates"] = BITRATES;
	convertTable["bitrate"] = BITRATE;
	convertTable["framerates"] = FRAMERATES;
	convertTable["framerate"] = FRAMERATE;
	convertTable["audio"] = AUDIO;
	convertTable["samplerates"] = SAMPLERATES;
	convertTable["samplerate"] = SAMPLERATE;
}

GuiSettingsParser::GuiSettingsParser() {
	resolutionRatio = "";
	resolutionName = "";
	initConvertTable();
}

GuiSettingsParser::~GuiSettingsParser() {}

bool GuiSettingsParser::parse(AVBox::GuiSettings& gui){
	//todo try catch
	std::string file = Settings::getSettings()->getValue(Settings::GUISETTINGS);

	guiSettings = new AVBox::GuiSettings();

	try{
		this->parse_file(file);
	}catch(std::exception& ex){
		std::cout<<"Parsovanie sa dojebalo: "<<ex.what()<<std::endl; //todo remove
		delete guiSettings;
		return false;
	}
	gui = *guiSettings;
	delete guiSettings;
	return true;
}
void GuiSettingsParser::on_start_document(){
	states.clear();
	resolutionRatio = "";
	resolutionName = "";
}
void GuiSettingsParser::on_end_document(){

}
void GuiSettingsParser::on_start_element(const Glib::ustring& name, const AttributeList& attributes){
	if (convertTable.find(name) != convertTable.end()){
		states.insert(convertTable[name]);
	}
	if (name == "resolutions"){
		for(iter = attributes.begin(); iter != attributes.end(); ++iter){
			if(iter->name == "ratio") {resolutionRatio = iter->value;}
		}
	}
	if (name == "resolution"){
		for(iter = attributes.begin(); iter != attributes.end(); ++iter){
			if(iter->name == "name") {resolutionName = iter->value;}
		}
	}
}
void GuiSettingsParser::on_end_element(const Glib::ustring& name){
	if (convertTable.find(name) != convertTable.end()){
		states.erase(convertTable[name]);
	}
}
void GuiSettingsParser::on_characters(const Glib::ustring& characters){
	if (states.count(VIDEO)){
		if (states.count(RESOLUTIONS) && states.count(RESOLUTION)){
			guiSettings->addVideoResolution(resolutionRatio, characters, resolutionName);
		}
		if (states.count(BITRATES) && states.count(BITRATE)){
			guiSettings->addVideoBitrate(characters);
		}
		if (states.count(FRAMERATES) && states.count(FRAMERATE)){
			guiSettings->addVideoFramerate(characters);
		}
	}
	if (states.count(AUDIO)){
		if (states.count(BITRATES) && states.count(BITRATE)){
			//todo add bitrate
		}
		if (states.count(SAMPLERATE) && states.count(SAMPLERATES)){
			//todo add samplerate
		}
	}
}
void GuiSettingsParser::on_comment(const Glib::ustring& text){

}
void GuiSettingsParser::on_warning(const Glib::ustring& text){

}
void GuiSettingsParser::on_error(const Glib::ustring& text){

}
void GuiSettingsParser::on_fatal_error(const Glib::ustring& text){

}
void GuiSettingsParser::on_cdata_block(const Glib::ustring& text){

}

} /* namespace XML */
