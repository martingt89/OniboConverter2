/*
 * format.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "format.h"
#include "../helper.h"

namespace ConverterOptions {

Format::Format(){
	name = "";
	formatType = FormatType::FORMAT_TYPE_VIDEO;
	encoders = Encoders();
}
Format::Format(std::string name, FormatType formatType, Encoders encoders) {
	this->name = name;
	this->formatType = formatType;
	this->encoders = encoders;

}
std::string Format::getName() const{
	return name;
}
Format::FormatType Format::getFormatType() const{
	return formatType;
}

Encoders Format::getEncoders() const{
	return encoders;
}


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

	assert(!exist, "Format name doesn't exist: '"+formatName+"'");
	return Format();
}

} /* namespace ConverterOptions */
