/*
 * helper.cpp
 *
 *  Created on: 9.8.2012
 *      Author: martint
 */

#include "helper.h"
#include <iostream>

void assert(bool expr, std::string message){
	if(!expr){
		std::cerr<<message<<std::endl;
		_exit(-1);
	}
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
