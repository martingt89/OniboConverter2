/*
 * helper.h
 *
 *  Created on: 23.7.2012
 *      Author: martint
 */

#ifndef HELPER_H_
#define HELPER_H_

#include <sstream>
#include <string>

int NSD(const int& x, const int& y);

std::string clearString(const std::string& str);

template<class T>
std::string operator << (const std::string &s,  T i){
	std::stringstream ss;
	ss << s;
	ss << i;
	return ss.str();
}

template<class T>
std::string toS(const T &number){
	std::stringstream ss;
	ss << number;
	return ss.str();
}

template<class T>
T toN(const std::string& number, const T&){
	if(number.size() == 0){
		return 0;
	}
	std::stringstream ss;
	T prem;
	ss << number;
	ss >> prem;
	return prem;
}

template<class T>
bool isN(const std::string& number, const T& x){
	return toS(toN(number, x)) == number;
}

#endif /* HELPER_H_ */
