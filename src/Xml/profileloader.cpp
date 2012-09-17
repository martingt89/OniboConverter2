/* ---------------------------------------------------------------------------
** Author: Martin Geier
** profileloader.cpp is part of OniboConverter2.
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

#include "profileloader.h"

#include "xmlparser.h"
#include "../xmlfilesdefinitions.h"

namespace Xml {

ProfileLoader::ProfileLoader() {}

ProfileLoader::~ProfileLoader() {}

bool ProfileLoader::load(const Path& profileFilePath,
		Profile::Configuration& configuration){

	XmlParser parser;
	XmlParserData data;
	if(!parser.parseFile(profileFilePath, &data)){
		return false;
	}
	auto& definition = XmlFilesDefinitions::getInstance()->getConfigurationTable();
	for(auto record : data){
		Profile::Configuration::Options option;
		if(definition.getOptionsFromList(record.first, option)){
			configuration.addProperty(option, record.second);
		}
	}
	return true;
}

} /* namespace Xml */
