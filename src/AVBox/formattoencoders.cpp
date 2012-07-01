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

void FormatToEncoders::addFormatEncoder(const std::string& format, const std::string& encoder){
	convertTable[format].push_back(encoder);
}

std::list<std::string> FormatToEncoders::getEncoders(const std::string& format) const{
	std::map<std::string, std::list<std::string> >::const_iterator it;

	it = convertTable.find(format);
	if(it != convertTable.end()){
		std::list<std::string> enc(it->second);
		return enc;
	}
	return std::list<std::string>();
}

} /* namespace AVBox */
