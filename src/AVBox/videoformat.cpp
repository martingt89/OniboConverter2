/*
 * videoformat.cpp
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#include "videoformat.h"

namespace AVBox {

VideoFormat::VideoFormat(const std::string& formatName) {
	format = formatName;
}
VideoFormat::VideoFormat(){
	format = "";
}
VideoFormat::~VideoFormat() {}

bool VideoFormat::operator==(const VideoFormat& enc) const{
	return this->format == enc.format;
}

std::string VideoFormat::getFormat() const{
	return format;
}

std::list<Encoder> VideoFormat::getAvailableEncoders(const FFTools::SuportedEncoders& suport,
		const AVBox::FormatToEncoders& encoder) const{
	std::list< Encoder >::const_iterator it;
	std::list<Encoder> list;
	std::string description;

	std::list<Encoder> encs = encoder.getEncoders(format);

	for(it = encs.begin(); it != encs.end(); it++){
		if(suport.isSuported(*it, description)){
			list.push_back(Encoder(*it, description));
		}
	}
	return list;
}

bool VideoFormatCmp::operator()(const VideoFormat &first, const VideoFormat &second) const{
	return first.getFormat() < second.getFormat();
}

} /* namespace AVBox */
