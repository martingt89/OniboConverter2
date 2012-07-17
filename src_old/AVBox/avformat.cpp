/*
 * avformat.cpp
 *
 *  Created on: 14.7.2012
 *      Author: martint
 */

#include "avformat.h"

namespace AVBox {

AVFormat::AVFormat(const std::string &name) {
	this->name = name;
}
AVFormat::AVFormat(){
	name = "";
}
AVFormat::~AVFormat() {
	// TODO Auto-generated destructor stub
}

void AVFormat::addEncoder(Encoder encoder){
	encoders.push_back(encoder);
}

std::string AVFormat::getName() const{
	return name;
}
} /* namespace AVBox */
