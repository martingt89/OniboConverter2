/*
 * convertsettings.cpp
 *
 *  Created on: 18.8.2012
 *      Author: martint
 */

#include "convertsettings.h"
#include <algorithm>
#include <iostream> //todo remove iostream
namespace Converter {

CppExtension::HashMap<ConvertSettings::Command, std::string> ConvertSettingsList::commandToStr;

ConvertSettings::ConvertSettings(Command command){
	settingsType = command;
}
ConvertSettings::ConvertSettings(std::string command){
	userDefind = command;
	settingsType = USER_DEFINED;
}
ConvertSettings::~ConvertSettings() {}

void ConvertSettings::addValue(std::string value){
	valuesList.push_back(value);
}
ConvertSettings::Command ConvertSettings::getCommand() const{
	return settingsType;
}
std::string ConvertSettings::getUserCommand(){
	return userDefind;
}
std::list<std::string> ConvertSettings::getValueList() const{
	return valuesList;
}
//

ConvertSettingsList::ConvertSettingsList(){
	if(commandToStr.isEmpty()){
		commandToStr.set(ConvertSettings::VBITRATE, "-b");
		commandToStr.set(ConvertSettings::ABITRATE, "-ab");
		commandToStr.set(ConvertSettings::FRAMERATE, "-r");
		commandToStr.set(ConvertSettings::SAMPLERATE, "-ar");
		commandToStr.set(ConvertSettings::VCODEC, "-vcodec");
		commandToStr.set(ConvertSettings::ACODEC, "-acodec");
		commandToStr.set(ConvertSettings::NOVIDEO, "-vn");
		commandToStr.set(ConvertSettings::NOAUDIO, "-an");
		commandToStr.set(ConvertSettings::SIZE, "-s");
		commandToStr.set(ConvertSettings::CHANNELS, "-ac");
		commandToStr.set(ConvertSettings::MULTITHREAD, "-thread");
		commandToStr.set(ConvertSettings::FFPRESET, "-fpre");
	}
}
ConvertSettingsList::ConvertSettingsList(const ConvertSettingsList& arguments){
	std::copy(arguments.arguments.begin(), arguments.arguments.end(), std::back_inserter(this->arguments));
}
void ConvertSettingsList::add(const ConvertSettings& argument){
	arguments.push_back(argument);
}
void ConvertSettingsList::add(const ConvertSettingsList& arguments){
	std::copy(arguments.arguments.begin(), arguments.arguments.end(), std::back_inserter(this->arguments));
}
void ConvertSettingsList::print() const{
	for(auto x : arguments){
		if(x.getCommand() == ConvertSettings::USER_DEFINED){
			std::cout<<" "<<x.getUserCommand();
		}else{
			std::cout<<" "<<commandToStr.get(x.getCommand());
		}
		for(auto v : x.getValueList()){
			std::cout<<" "<<v;
		}
	}
	std::cout<<std::endl;
}
std::list<std::string> ConvertSettingsList::getArguments() const {
	std::list<std::string> args;
	for(auto x : arguments){
		if(x.getCommand() == ConvertSettings::USER_DEFINED){
			args.push_back(x.getUserCommand());
		}else{
			if(x.getCommand() == ConvertSettings::MULTITHREAD){
				continue;
			}
			args.push_back(commandToStr.get(x.getCommand()));
		}
		for(auto v : x.getValueList()){
			args.push_back(v);	//todo trim by spaces
		}
	}
	return args;
}
std::string ConvertSettingsList::getContainerName() const{
	auto iter = std::find_if(arguments.begin(), arguments.end(), [](const ConvertSettings& settings)->bool{
		return settings.getCommand() == ConvertSettings::CONTAINER;
	});
	if(iter != arguments.end()){
		std::string container = *iter->getValueList().begin();
		return container;
	}
	return std::string();
}
} /* namespace Converter */
