/*
 * format.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "format.h"

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
		videoFormats[format.getName()] = format;
	}else{
		audioFormats[format.getName()] = format;
	}
}
std::list<Format> Formats::getVideoFormatsList() const{
	std::list<Format> videoFormatsList;
	for(auto videoIterator = videoFormats.begin(); videoIterator != videoFormats.end(); ++videoIterator){
		videoFormatsList.push_back(videoIterator->second);
	}
	return videoFormatsList;
}
std::list<Format> Formats::getAudioFormatsList() const{
	std::list<Format> audioFormatsList;
	for(auto audioIterator = audioFormats.begin(); audioIterator != audioFormats.end(); ++audioIterator){
		audioFormatsList.push_back(audioIterator->second);
	}
	return audioFormatsList;
}
Format Formats::getFormatByName(std::string formatName) const{	//todo format not found
	auto videoIterator = videoFormats.find(formatName);
	if(videoIterator != videoFormats.end()){
		return videoIterator->second;
	}
	auto audioIterator = audioFormats.find(formatName);
	if(audioIterator != audioFormats.end()){
		return audioIterator->second;
	}

	return Format();
}

} /* namespace ConverterOptions */
