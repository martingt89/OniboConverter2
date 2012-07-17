/*
 * formatsparser.cpp
 *
 *  Created on: 14.7.2012
 *      Author: martint
 */

#include "formatsparser.h"
#include "../Tools/settings.h"
#include <iostream> //todo remove

namespace XML {

FormatsParser::FormatsParser(const std::list<AVBox::Encoder> supportedEncoders) {

	inEnc = false;
	presentsPrefix = "";

	std::list<AVBox::Encoder>::const_iterator it;
	for(it = supportedEncoders.begin(); it != supportedEncoders.end(); ++it){
		this->supportedEncoders[it->getName()] = *it;
	}

	std::string file = Settings::getSettings()->getValue(Settings::ENCODERS);
	try{
		this->parse_file(file);
	}catch(std::exception& ex){
		std::cout<<"Parsovanie sa dojebalo: "<<ex.what()<<std::endl; //todo remove
	}
}

FormatsParser::~FormatsParser() {}

std::list<AVBox::AVFormat> FormatsParser::getFormats() const{
	return formats;
}

void FormatsParser::on_start_element(const Glib::ustring& name, const AttributeList& attributes){
	if(name == "format"){
		for(xmlpp::SaxParser::AttributeList::const_iterator
				iter = attributes.begin(); iter != attributes.end(); ++iter){
			if(iter->name == "id") {
				formats.push_front(AVBox::AVFormat(iter->value));
			}
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
void FormatsParser::on_end_element(const Glib::ustring& name){
	if(name == "encoder"){
		inEnc = false;
		presentsPrefix = "";
	}
}

void FormatsParser::on_characters(const Glib::ustring& characters) {
	AVBox::Encoder encoder;
	if(inEnc && actualFormat.size() > 0 && getEncoder(characters, encoder)){
		if(presentsPrefix.size() != 0){
			encoder.addOptions("ffprefix", presentsPrefix);
		}
		addEncoderToFormat(formats, encoder);
	}
}

void FormatsParser::addEncoderToFormat(std::list<AVBox::AVFormat> &formats, const AVBox::Encoder& encoder) {
	if (formats.begin() != formats.end()) {
		formats.begin()->addEncoder(encoder);
	}
}

bool FormatsParser::getEncoder(const std::string& encoderName, AVBox::Encoder &encoder){
	std::map<std::string, AVBox::Encoder>::iterator it = supportedEncoders.find(encoderName);
	if(it != supportedEncoders.end()){
		encoder = it->second;
		return true;
	}
	return false;
}
} /* namespace XML */
