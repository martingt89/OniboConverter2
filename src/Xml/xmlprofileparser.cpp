/*
 * xmlprofileparser.cpp
 *
 *  Created on: 12.8.2012
 *      Author: martint
 */

#include "xmlprofileparser.h"
#include <iostream>		//todo remove
#include <algorithm>
#include "../helper.h"

namespace Xml {

XmlProfileParser::XmlProfileParser() {
	actualProfile = NULL;
}

XmlProfileParser::~XmlProfileParser() {}

bool XmlProfileParser::parseFile(const Path& filePath, Profile::Profile& profile){
	path.clear();
	actualProfile = &profile;
	try{
		this->parse_file(filePath.getPath());
	}catch(std::exception& ex){
		std::cout<<"Parsovanie sa dojebalo: "<<ex.what()<<std::endl; //todo log
		actualProfile = NULL;
		return false;
	}
	actualProfile = NULL;
	return true;
}
void XmlProfileParser::on_start_element(const Glib::ustring& name, const AttributeList& attributes){
	path.push_back(name);
}
void XmlProfileParser::on_end_element(const Glib::ustring& name){
	path.pop_back();
}
void XmlProfileParser::on_characters(const Glib::ustring& characters){
	auto& xmlProfileTable = XmlFilesDefinitions::getInstance()->getProfileTable();
	if(actualProfile){
		std::string value = clearString(characters);
		if(value.size() > 0){
			Profile::Profile::Options options;
			if(!xmlProfileTable.getOptionsFromList(path, options)){
				 options = Profile::Profile::UNKNOWN_OPT;
			}
			actualProfile->addProperty(options, value);
		}
	}
}

} /* namespace Xml */
