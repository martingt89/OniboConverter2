/*
 * format.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "format.h"
#include "../helper.h"

namespace MediaElement {

Format::Format(){
	name = "";
	formatType = FormatType::FORMAT_TYPE_VIDEO;
}
Format::Format(std::string name, FormatType formatType) {
	this->name = name;
	this->formatType = formatType;
}
std::string Format::getName() const{
	return name;
}
//std::string Format::getHash() const{
//	return name;
//}
std::string Format::readableForm() const{
	return name;
}
Format::FormatType Format::getFormatType() const{
	return formatType;
}
bool Format::operator<(const Format& second) const{
	return this->name < second.name;
}
bool Format::operator==(const Format& second) const{
	return this->name == second.name;
}
//*******************************************************************
void Formats::addFormat(const Format& format){
	if(format.getFormatType() == Format::FORMAT_TYPE_VIDEO){
		videoFormats.set(format.getName(), format);
	}else{
		audioFormats.set(format.getName(), format);
	}
}
std::list<Format> Formats::getVideoFormatsList() const{
	return videoFormats.getListOfValues();
}
std::list<Format> Formats::getAudioFormatsList() const{
	return audioFormats.getListOfValues();
}
bool Formats::isAudioOnly() const{
	return videoFormats.isEmpty();
}
Format Formats::getFormatByName(std::string formatName) const{
	bool exist = false;
	Format format = videoFormats.get(formatName, exist);
	if(exist){
		return format;
	}

	format = audioFormats.get(formatName, exist);
	if(exist){
		return format;
	}

	assert(exist, "Format name doesn't exist: '"+formatName+"'");
	return Format();
}
bool Formats::getFormatByName(std::string formatName, const Format::FormatType& type, Format& format) const{
	if(type == Format::FORMAT_TYPE_VIDEO){
		bool exist = false;
		format = videoFormats.get(formatName, exist);
		if(exist){
			return true;
		}
	}
	if(type == Format::FORMAT_TYPE_AUDIO){
		bool exist = false;
		format = audioFormats.get(formatName, exist);
		if(exist){
			return true;
		}
	}
	return false;
}

} /* namespace MediaElement */
