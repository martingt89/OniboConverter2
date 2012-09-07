/*
 * profileparser.cpp
 *
 *  Created on: 7.9.2012
 *      Author: martin
 */

#include "profileparser.h"

#include "xmlparser.h"
#include "../xmlfilesdefinitions.h"

namespace Xml {

ProfileParser::ProfileParser() {}

ProfileParser::~ProfileParser() {}

bool ProfileParser::load(const Path& profileFilePath, Profile::Profile& profile){
	XmlParser parser;
	XmlParserData data;
	if(!parser.parseFile(profileFilePath, &data)){
		return false;
	}
	auto& definition = XmlFilesDefinitions::getInstance()->getProfileTable();
	for(auto record : data){
		Profile::Profile::Options option;
		if(definition.getOptionsFromList(record.first, option)){
			profile.addProperty(option, record.second);
		}
	}
	return true;
}

} /* namespace Xml */
