/*
 * convertparser.cpp
 *
 *  Created on: 30.8.2012
 *      Author: martint
 */

#include "convertparser.h"
#include "../helper.h"
#include <iostream>

namespace Converter {

ConvertParser::ConvertParser(const double& duration) : duration(duration),
		lineRegex(".*time=([0-9]+\\.[0-9]+).*") {
	aktualTime = 0;
}

ConvertParser::~ConvertParser() {
	// TODO Auto-generated destructor stub
}

void ConvertParser::processLine(const std::string& line, double& fraction, int& remainingTime){
	RegexTools::Matcher matcher = lineRegex.getMatcher(line);
	double aktime = aktualTime;
	if(matcher.find()){
		std::string time = matcher.getGroup(1);
		aktime = toN(time, double());
	}else{
		std::cout<<line<<std::endl;
	}
	if(aktime > aktualTime){
		aktualTime = aktime;
	}

	fraction = aktualTime / duration + 0.005;
	remainingTime = 300;	//todo implement remaining time
}
} /* namespace Converter */
