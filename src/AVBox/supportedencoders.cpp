/*
 * supportedencoders.cpp
 *
 *  Created on: 6.7.2012
 *      Author: martint
 */

#include "supportedencoders.h"
#include <iostream> //todo remove
namespace AVBox {

bool SupportedEncoders::isSuported(const AVBox::Encoder& name, std::string& description) const {
	std::map<std::string, EncoderFFData>::const_iterator it;
		if((it = suportedEndcoders.find(name.getEncoder())) != suportedEndcoders.end()){
		description = it->second.description;
		return true;
	}
	return false;
}

void SupportedEncoders::addEncoder(const EncoderFFData& encoder){
	suportedEndcoders[encoder.encoder] = encoder;
}

} /* namespace AVBox */
