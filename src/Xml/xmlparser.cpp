/*
 * xmlparser.cpp
 *
 *  Created on: 7.9.2012
 *      Author: martin
 */

#include "xmlparser.h"
#include "../helper.h"
#include <iostream>

namespace Xml {

XmlParser::XmlParser() {
	data = NULL;
}

XmlParser::~XmlParser() {
	// TODO Auto-generated destructor stub
}

bool XmlParser::parseFile(const Path& filePath, XmlParserData* data){
	this->data = data;
	try{
		this->parse_file(filePath.getPath());
	}catch(std::exception& ex){
		std::cout<<"Parse error: "<<ex.what()<<std::endl; //todo log
		data = NULL;
		return false;
	}
	data = NULL;
	return true;
}

void XmlParser::on_start_element(const Glib::ustring& name, const AttributeList& attributes){
	path.push_back(name);
}
void XmlParser::on_end_element(const Glib::ustring& name){
	path.pop_back();
}
void XmlParser::on_characters(const Glib::ustring& characters){
		if(data){
			std::string value = clearString(characters);
			if(value.size() > 0){
				std::pair<std::list<std::string>, std::string> pair;
				pair.first = path;
				pair.second = value;
				data->push_back(pair);
			}
		}
}

} /* namespace Xml */
