/*
 * supportedencoders.cpp
 *
 *  Created on: 27.7.2012
 *      Author: martint
 */

#include "supportedencoders.h"


namespace ConverterOptions {

void SupportedEncoders::addEncoder(const std::string& encoderName, const std::string& description){
	encoderNameToDescr.set(encoderName, description);
}
bool SupportedEncoders::isSupported(const std::string& encoderName) const{
	return encoderNameToDescr.isExistKey(encoderName);
}
std::string SupportedEncoders::getEncoderDescription(const std::string& encoderName) const{
	return encoderNameToDescr.get(encoderName);
}

} /* namespace ConverterOptions */
