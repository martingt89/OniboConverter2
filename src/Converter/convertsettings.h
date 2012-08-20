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
		MULTITHREAD
	};
public:
	ConvertSettings(Command command);
	void addValue(std::string value);
	virtual ~ConvertSettings();
	Command getCommand();
	std::list<std::string> getValueList();
private:
	std::list<std::string> valuesList;
	Command settingsType;
};

class ConvertSettingsList{
public:
	ConvertSettingsList();
	ConvertSettingsList(const ConvertSettingsList& arguments);
	void add(const ConvertSettings& argument);
	void add(const ConvertSettingsList& argument);
	void print();
private:
	std::list<ConvertSettings> arguments;
	static CppExtension::HashMap<ConvertSettings::Command, std::string> commandToStr;
};


} /* namespace Converter */
#endif /* ARGUMENT_H_ */
