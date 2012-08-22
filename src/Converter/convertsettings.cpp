/*
 * convertsettings.cpp
 *
 *  Created on: 18.8.2012
 *      Author: martint
 */

#include "convertsettings.h"
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
ConvertSettings::Command ConvertSettings::getCommand(){
	return settingsType;
}
std::string ConvertSettings::getUserCommand(){
	return userDefind;
}
std::list<std::string> ConvertSettings::getValueList(){
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
} /* namespace Converter */
