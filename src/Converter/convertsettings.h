/*
 * convertsettings.h
 *
 *  Created on: 18.8.2012
 *      Author: martint
 */

#ifndef ARGUMENT_H_
#define ARGUMENT_H_

#include <list>
#include <string>
#include "../CppExtension/hashmap.h"

namespace Converter {

class ConvertSettings {
public:
	enum Command{
		VBITRATE, ABITRATE, FRAMERATE, SAMPLERATE, VCODEC, ACODEC, NOVIDEO, NOAUDIO, SIZE, CHANNELS,
		MULTITHREAD, FFPRESET, USER_DEFINED, CONTAINER
	};
public:
	ConvertSettings(Command command);
	ConvertSettings(std::string command);
	void addValue(std::string value);
	virtual ~ConvertSettings();
	Command getCommand() const;
	std::string getUserCommand();
	std::list<std::string> getValueList() const;
private:
	std::list<std::string> valuesList;
	std::string userDefind;
	Command settingsType;
};

class ConvertSettingsList{
public:
	ConvertSettingsList();
	ConvertSettingsList(const ConvertSettingsList& arguments);
	void add(const ConvertSettings& argument);
	void add(const ConvertSettingsList& argument);
	std::string getPrintString() const;
	std::list<std::string> getArguments() const;
	std::string getContainerName() const;
private:
	std::list<ConvertSettings> arguments;
	static CppExtension::HashMap<ConvertSettings::Command, std::string> commandToStr;
};


} /* namespace Converter */
#endif /* ARGUMENT_H_ */
