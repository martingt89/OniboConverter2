/*
 * XmlFilesDefinitions.h
 *
 *  Created on: 6.9.2012
 *      Author: martin
 */

#ifndef XMLFILESDEFINITIONS_H_
#define XMLFILESDEFINITIONS_H_

#include "userpreferences.h"

#include "helper.h"
#include "Xml/converttable.h"
#include "Profile/configuration.h"

class XmlFilesDefinitions{
public:
	static XmlFilesDefinitions* getInstance();
	Xml::ConvertTable<UserPreferences::UserPreferencesOpt>& getUserPreferencesTable();
	Xml::ConvertTable<Profile::Configuration::Options>& getConfigurationTable();
private:
	XmlFilesDefinitions();
	XmlFilesDefinitions(const XmlFilesDefinitions&);
	Xml::ConvertTable<UserPreferences::UserPreferencesOpt> userPreferences;
	Xml::ConvertTable<Profile::Configuration::Options> profilConfiguration;
	static XmlFilesDefinitions* instance;
};


#endif /* XMLFILESDEFINITIONS_H_ */
