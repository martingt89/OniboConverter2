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

static const unsigned int NUM_OF_SAVED_RECORD = 25;

ConvertParser::ConvertParser(const double& duration) : duration(duration),
		lineRegex(".*time=([0-9]+\\.[0-9]+).*") {
	aktualTime = 0;
	lastWorldTime = getAktualTimeMikro();
}

ConvertParser::~ConvertParser() {
	// TODO Auto-generated destructor stub
}

bool ConvertParser::processLine(const std::string& line, double& fraction, int& remainingTime){
	remainingTime = -1;
	fraction = -1;
	RegexTools::Matcher matcher = lineRegex.getMatcher(line);
	double aktime = aktualTime;
	if(matcher.find()){
		std::string time = matcher.getGroup(1);
		aktime = toN(time, double());
//		std::cout<<line<<std::endl;
	}else{
//		std::cout<<line<<std::endl;
		return false;
	}
	if(aktime > aktualTime){
		long aktualWorldTime = getAktualTimeMikro();
		double elapsed = (aktualWorldTime - lastWorldTime)/1000000.0;
		lastWorldTime = aktualWorldTime;
		double diff = aktime - aktualTime;
		aktualTime = aktime;
		addRecord(diff, elapsed);
		double speed = getNumSecPerSec();
		double estimate = duration - aktualTime;
		remainingTime = estimate / speed;
	}else{
		remainingTime = -1;
	}

	fraction = aktualTime / duration + 0.005;
	return true;
}
void ConvertParser::addRecord(double diff, double elapsed){
	if(diffAndTime.size() >= NUM_OF_SAVED_RECORD){
		diffAndTime.pop_front();
	}
	diffAndTime.push_back(std::make_pair(diff, elapsed));
}
double ConvertParser::getNumSecPerSec(){
	double diffTotal = 0;
	double elapsedTotal = 0;
	for(auto x : diffAndTime){
		diffTotal += x.first;
		elapsedTotal += x.second;
	}
	return diffTotal / elapsedTotal;
}
} /* namespace Converter */
