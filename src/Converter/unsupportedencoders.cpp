/*
 * unsupportedencoders.cpp
 *
 *  Created on: 11.9.2012
 *      Author: martin
 */

#include "unsupportedencoders.h"
#include <iostream>
namespace Converter {


void UnsupportedEncoders::addUnsupportedEncoder(const std::string &name,
		const std::string &description, PriorityLevel level){
	encoders.push_back(std::make_pair(name, level));
}
bool UnsupportedEncoders::isEmpty(){
	return encoders.empty();
}

std::list<std::pair<std::string, UnsupportedEncoders::PriorityLevel> > UnsupportedEncoders::getEncoders() const{
	return encoders;
}

} /* namespace Converter */
