/* ---------------------------------------------------------------------------
** Author: Martin Geier
** xmlfilesdefinitions.h is part of OniboConverter2.
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
