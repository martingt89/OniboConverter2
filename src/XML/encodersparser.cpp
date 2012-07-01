/*
 * encodersparser.cpp
 *
 *  Created on: 30.6.2012
 *      Author: martint
 */

#include "encodersparser.h"
#include "../settings.h"
#include <iostream>//todo remove

namespace XML {

EncodersParser::EncodersParser() {
	encoders = NULL;
	actualFormat = "";
	inEnc = false;
}

EncodersParser::~EncodersParser() {}

bool EncodersParser::parse(AVBox::FormatToEncoders& enc){
	//todo try - catch
	std::string file = Settings::getSettings()->getValue(Settings::ENCODERS);

	encoders = new AVBox::FormatToEncoders();
	try{
		this->parse_file(file);
	}catch(std::exception& ex){
		std::cout<<"Parsovanie sa dojebalo: "<<ex.what()<<std::endl; //todo remove
		delete encoders;
		return false;
	}
	enc = *encoders;
	delete encoders;
	return true;
}
void EncodersParser::on_start_document(){}
void EncodersParser::on_end_document(){}
void EncodersParser::on_start_element(const Glib::ustring& name, const AttributeList& attributes){
	if(name == "format"){
		for(xmlpp::SaxParser::AttributeList::const_iterator
				iter = attributes.begin(); iter != attributes.end(); ++iter){
			if(iter->name == "id") {actualFormat = iter->value; break;}
		}
	}
	if(name == "encoder"){
		inEnc = true;
	}
}
void EncodersParser::on_end_element(const Glib::ustring& name){
	if(name == "encoder"){
		inEnc = false;
	}
	if(name == "format"){
		actualFormat = "";
	}
}
void EncodersParser::on_characters(const Glib::ustring& characters){
	if(inEnc && actualFormat.size() > 0 && encoders){
		encoders->addFormatEncoder(actualFormat, characters);
	}
}
void EncodersParser::on_comment(const Glib::ustring& text){}
void EncodersParser::on_warning(const Glib::ustring& text){}
void EncodersParser::on_error(const Glib::ustring& text){}
void EncodersParser::on_fatal_error(const Glib::ustring& text){}
void EncodersParser::on_cdata_block(const Glib::ustring& text){}

} /* namespace XML */
