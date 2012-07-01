/*
 * audioformat.cpp
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#include "audioformat.h"

namespace AVBox {

AudioFormat::AudioFormat(const std::string& formatName) {
	format = formatName;
}
AudioFormat::AudioFormat(){
	format = "";
}
AudioFormat::~AudioFormat() {}

bool AudioFormat::operator==(const AudioFormat& enc) const{
	return this->format == enc.format;
}

std::string AudioFormat::getFormat() const{
	return format;
}
std::list<Encoder> AudioFormat::getAvailableEncoders(const FFTools::SuportedEncoders& suport,
		const AVBox::FormatToEncoders& encoder) const{

	std::list< std::string >::const_iterator it;
	std::list<Encoder> list;
	std::string description;

	std::list<std::string> encs = encoder.getEncoders(format);

	for(it = encs.begin(); it != encs.end(); it++){
		if(suport.isSuported(*it, description)){
			list.push_back(Encoder(*it, description));
		}
	}
	return list;
}

bool AudioFormatCmp::operator()(const AudioFormat &first, const AudioFormat &second) const{
	return first.getFormat() == second.getFormat();
}

} /* namespace AVBox */
