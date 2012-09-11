/*
 * profileloader.cpp
 *
 *  Created on: 7.9.2012
 *      Author: martin
 */

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
