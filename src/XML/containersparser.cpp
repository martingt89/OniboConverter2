/*
 * containersparser.cpp
 *
 *  Created on: 30.6.2012
 *      Author: martint
 */

#include "containersparser.h"
#include <iostream>
#include "../settings.h"
namespace XML {

ContainersParser::ContainersParser() {
	tmpContainer = NULL;
	formatType = NONE;
	setCodec = false;
	avBox = NULL;
}

ContainersParser::~ContainersParser() {}

bool ContainersParser::parse(AVBox::AVBox& box){
	//todo try - catch
	std::string file = Settings::getSettings()->getValue(Settings::CONTAINERS);
	avBox = new AVBox::AVBox();
	try{
		this->parse_file(file);
	}catch(std::exception& ex){
		std::cout<<"Parsovanie sa dojebalo: "<<ex.what()<<std::endl;
		delete avBox;
		return false;
	}

	box = *avBox;
	delete avBox;
	return true;
}

void ContainersParser::on_start_document(){}
void ContainersParser::on_end_document(){}
void ContainersParser::on_start_element(const Glib::ustring& name, const AttributeList& attributes){
	if(name == "container"){
		std::string containerName = "";
		for(xmlpp::SaxParser::AttributeList::const_iterator
				iter = attributes.begin(); iter != attributes.end(); ++iter){
			if(iter->name == "name") {containerName = iter->value; break;}
		}
		if(containerName.size() > 0){
			tmpContainer = new AVBox::Container(containerName);
		}
	}
	if(name  == "video"){
		formatType = VIDEO;
	}else if(name == "audio"){
		formatType = AUDIO;
	}
	if(name == "codec"){
		setCodec = true;
	}
}
void ContainersParser::on_end_element(const Glib::ustring& name){
	if(name == "codec"){
		setCodec = false;
	}
	if(name == "video" || name == "audio"){
		formatType = NONE;
	}
	if(name == "container"){
		if(tmpContainer){
			avBox->addContainer(*tmpContainer);
			delete tmpContainer;
			tmpContainer = NULL;
		}
	}
}
void ContainersParser::on_characters(const Glib::ustring& characters){
	if(setCodec && tmpContainer){
		if(formatType == VIDEO){
			tmpContainer->addVideoFormat(AVBox::VideoFormat(characters));
		}else if(formatType == AUDIO){
			tmpContainer->addAudioFormat(AVBox::AudioFormat(characters));
		}
	}
}
void ContainersParser::on_comment(const Glib::ustring& text){}
void ContainersParser::on_warning(const Glib::ustring& text){}
void ContainersParser::on_error(const Glib::ustring& text){}
void ContainersParser::on_fatal_error(const Glib::ustring& text){}
void ContainersParser::on_cdata_block(const Glib::ustring& text){}
} /* namespace XML */
