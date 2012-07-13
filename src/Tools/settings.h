/*
 * settings.h
 *
 *  Created on: 20.6.2012
 *      Author: martint
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <exception>
#include <string>
#include <map>


class SettingsNotFoundException : public std::exception {
public:
	SettingsNotFoundException(std::string message){
		this->message = message;
	};
	virtual const char* what() const throw(){
		return message.c_str();
	}
	virtual ~SettingsNotFoundException() throw () {};
private:
	std::string message;
};

class Settings {
private:
	Settings(){};
	virtual ~Settings(){};
	Settings(const Settings&);
	void operator=(const Settings&);
public:
	enum Set{
		FFPATH, CONTAINERS, ENCODERS, GUISETTINGS, FFPRESENTSFOLDER, OUTPUTFOLDER
	};
	std::string toString(Set s){
		switch(s){
			case FFPATH: return "FFPATH";
			case CONTAINERS: return "CONTAINERS";
			case ENCODERS: return "ENCODERS";
			case GUISETTINGS: return "GUISETTINGS";
			case FFPRESENTSFOLDER: return "FFPRESENTSFOLDER";
			case OUTPUTFOLDER: return "OUTPUTFOLDER";
			default: return "INVALID ENUM";
		}
	};
	static Settings* getSettings();
	std::string getValue(Set name) throw (SettingsNotFoundException);
	void setValue(Set name, std::string value);
private:
	std::map<Set, std::string> content;
	static Settings* settings;
};

#endif /* SETTINGS_H_ */
