/*
 * helper.h
 *
 *  Created on: 21.6.2012
 *      Author: martint
 */

#ifndef HELPER_H_
#define HELPER_H_

#include <sstream>
#include <string>

template<class T>
std::string operator+(const std::string &s,  T i){
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

#endif /* HELPER_H_ */
