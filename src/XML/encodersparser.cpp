/*
 * encodersparser.cpp
 *
 *  Created on: 30.6.2012
 *      Author: martint
 */

#include "encodersparser.h"
#include "../Tools/settings.h"
#include <iostream>//todo remove

namespace XML {

EncodersParser::EncodersParser() {
	encoders = NULL;
	actualFormat = "";
	inEnc = false;
	presentsPrefix = "";
}

EncodersParser::~EncodersParser() {}

bool EncodersParser::parse(AVBox::FormatToEncoders* enc){
	//todo try catch
	std::string file = Settings::getSettings()->getValue(Settings::ENCODERS);

	encoders = enc;
	try{
		this->parse_file(file);
	}catch(std::exception& ex){
		std::cout<<"Parsovanie sa dojebalo: "<<ex.what()<<std::endl; //todo remove
		encoders = NULL;
		return false;
	}
	encoders = NULL;
	return true;
}
void EncodersParser::on_start_document(){}
void EncodersParser::on_end_document(){}
void EncodersParser::on_start_element(const Glib::ustring& name, const AttributeList& attributes){
	if(name == "format"){
		for(xmlpp::SaxParser::AttributeList::const_iterator
				iter = attributes.begin(); iter != attributes.end(); ++iter){
			if(iter->name == "id") {actualFormat = iter->value;}
		}
	}
	if(name == "encoder"){
		inEnc = true;
		for(xmlpp::SaxParser::AttributeList::const_iterator
						iter = attributes.begin(); iter != attributes.end(); ++iter){
			if(iter->name == "ffprefix") {presentsPrefix = iter->value;}	//todo supovat do listu parov
		}
	}
}
void EncodersParser::on_end_element(const Glib::ustring& name){
	if(name == "encoder"){
		inEnc = false;
		presentsPrefix = "";
	}
	if(name == "format"){
		actualFormat = "";
	}
}
void EncodersParser::on_characters(const Glib::ustring& characters){
	if(inEnc && actualFormat.size() > 0 && encoders){
		encoders->addFormatEncoder(actualFormat, characters, presentsPrefix);
	}
}
void EncodersParser::on_comment(const Glib::ustring& text){}
void EncodersParser::on_warning(const Glib::ustring& text){}
void EncodersParser::on_error(const Glib::ustring& text){}
void EncodersParser::on_fatal_error(const Glib::ustring& text){}
void EncodersParser::on_cdata_block(const Glib::ustring& text){}

} /* namespace XML */
