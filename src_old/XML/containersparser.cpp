/*
 * containersparser.cpp
 *
 *  Created on: 30.6.2012
 *      Author: martint
 */

#include "containersparser.h"
#include <iostream>
#include "../Tools/settings.h"
namespace XML {

ContainersParser::ContainersParser(const std::list<AVBox::AVFormat>& formats) {
	setFormat = false;
	std::string file = Settings::getSettings()->getValue(Settings::CONTAINERS);

	std::list<AVBox::AVFormat>::const_iterator it;
	for(it = formats.begin(); it != formats.end(); ++it){
		this->formats[it->getName()] = *it;
	}

	try{
		this->parse_file(file);
	}catch(std::exception& ex){
		std::cout<<"Parsing Error: "<<ex.what()<<std::endl;
	}
}

ContainersParser::~ContainersParser() {}

std::map<std::string, AVBox::Container> ContainersParser::getContainersWithNames() const{
	std::map<std::string, AVBox::Container> containersWithNames;
	std::list<AVBox::Container>::const_iterator it;
	for(it = containers.begin(); it != containers.end(); ++it){
		containersWithNames[it->getName()] = *it;
	}
	return containersWithNames;
}

void ContainersParser::on_start_element(const Glib::ustring& name, const AttributeList& attributes){
	if(name == "container"){
		std::string containerName = "";
		for(xmlpp::SaxParser::AttributeList::const_iterator
				iter = attributes.begin(); iter != attributes.end(); ++iter){
			if(iter->name == "name") {containerName = iter->value; break;}
		}
		if(containerName.size() > 0){
			containers.push_front(AVBox::Container(containerName));
		}
	}
	if(name == "codec"){
		setFormat = true;
	}
}
void ContainersParser::on_end_element(const Glib::ustring& name){
	if(name == "codec"){
		setFormat = false;
	}
}
void ContainersParser::on_characters(const Glib::ustring& characters){
	if(setFormat && formats.count(characters) > 0){
		if(containers.size() > 0){
			containers.begin()->addAVFormat(formats[characters]);
		}
	}
}
} /* namespace XML */
