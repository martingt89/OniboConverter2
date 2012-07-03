/*
 * formattoencoders.cpp
 *
 *  Created on: 30.6.2012
 *      Author: martint
 */

#include "formattoencoders.h"
#include <iostream>

namespace AVBox {

FormatToEncoders::FormatToEncoders() {}

FormatToEncoders::~FormatToEncoders() {}

void FormatToEncoders::addFormatEncoder(const std::string& format, const std::string& encoder, std::string ffprefix=""){
	Encoder enc(encoder);
	enc.addOptions("ffprefix", ffprefix);

	convertTable[format].push_back(enc);
}

std::list<Encoder> FormatToEncoders::getEncoders(const std::string& format) const{
	std::map<std::string, std::list<Encoder> >::const_iterator it;

	it = convertTable.find(format);
	if(it != convertTable.end()){
		std::list<Encoder> enc(it->second);
		return enc;
	}
	return std::list<Encoder>();
}

} /* namespace AVBox */
