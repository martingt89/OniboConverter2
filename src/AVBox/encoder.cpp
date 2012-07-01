/*
 * encoder.cpp
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#include "encoder.h"

namespace AVBox {

Encoder::Encoder(const std::string& encoder, const std::string& description) {
	this->encoder = encoder;
	this->description = description;
}

Encoder::~Encoder() {}

} /* namespace AVBox */
