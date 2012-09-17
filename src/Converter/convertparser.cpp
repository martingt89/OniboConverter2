/* ---------------------------------------------------------------------------
** Author: Martin Geier
** convertparser.cpp is part of OniboConverter2.
**
** OniboConverter2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
** -------------------------------------------------------------------------*/

#include "convertparser.h"
#include "../helper.h"
#include <iostream>

namespace Converter {

static const unsigned int NUM_OF_SAVED_RECORD = 25;

ConvertParser::ConvertParser(const double& duration) : duration(duration),
		colonTimeFormat(".*time=([0-9:]+\\.[0-9]+).*"){
	aktualTime = 0;
	lastWorldTime = getAktualTimeMikro();
}

ConvertParser::~ConvertParser() {}

bool ConvertParser::processLine(const std::string& line, double& fraction, int& remainingTime){
	remainingTime = -1;
	fraction = -1;
	RegexTools::Matcher matcher = colonTimeFormat.getMatcher(line);
	double aktime = aktualTime;
	if(matcher.find()){
		std::string time = matcher.getGroup(1);
		aktime = toSecondTime(time);
	}else{
		return false;
	}
	if(duration >= 0){
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
	}else{
		remainingTime = 0;
		fraction = 0;
	}
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
double ConvertParser::toSecondTime(const std::string& time){
	std::string::size_type pos;
	std::string tmpTime = time;
	double secondTime = 0;
	while((pos = tmpTime.find(":"))!= std::string::npos){
		std::string sub = tmpTime.substr(0, pos);
		secondTime = secondTime*60 + toN(sub, int());
		tmpTime = tmpTime.substr(pos+1);
	}
	secondTime = secondTime*60 + toN(tmpTime, int());
	return secondTime;
}

} /* namespace Converter */
