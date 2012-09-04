/*
 * helper.cpp
 *
 *  Created on: 9.8.2012
 *      Author: martint
 */

#include "helper.h"
#include <iostream>
#include <sys/time.h>

void assert(bool expr, std::string message){
	if(!expr){
		std::cerr<<message<<std::endl;
		_exit(-1);
	}
}

long getAktualTimeMikro(){
	timeval time;
	gettimeofday(&time, NULL);
	long millis = (time.tv_sec * 1000000) + time.tv_usec;
	return millis;
}

std::string getActualTimeMiliSec(){
	timeval time;
	gettimeofday(&time, NULL);
	long millis = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return toS(millis);
}

int NSD(const int& x, const int& y){
	int nsd = 0;
	int b = y;
	int a = x;
	if (b == 0){
		nsd = a;
	}else{
		nsd = NSD(b, a % b);
	}
	return nsd;
}

std::string clearString(const std::string& str){
	std::string::size_type pos = str.find_first_not_of(" \n\t");
	if(pos == std::string::npos){
		return "";
	}
	std::string beginClear = str.substr(pos);
	pos = beginClear.find_last_not_of(" \n\t");
	if(pos == std::string::npos){
		return "";
	}
	return beginClear.substr(0, pos+1);
}
std::list<std::string> trimStringBy(const std::string& string, const std::string& delimiter){
	std::list<std::string> output;
	std::string tmpString = string;
	std::string::size_type pos = 0;
	while((pos = tmpString.find(delimiter)) != std::string::npos){
		if(pos > 0){
			output.push_back(tmpString.substr(0, pos));
		}
		tmpString = tmpString.substr(pos+delimiter.size());
	}
	if(tmpString.size() != 0){
		output.push_back(tmpString);
	}
	return output;
}
