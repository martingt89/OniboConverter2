/* ---------------------------------------------------------------------------
** Author: Martin Geier
** helper.h is part of OniboConverter2.
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

#ifndef HELPER_H_
#define HELPER_H_

#include <sstream>
#include <string>
#include <list>
#include <initializer_list>


long getAktualTimeMikro();

int NSD(const int& x, const int& y);

std::string clearString(const std::string& str);

void assert(bool expr, std::string message);

std::string getActualTimeMiliSec();

std::list<std::string> trimStringBy(const std::string& string, const std::string& delimiter);

std::list<std::string> toList(const std::initializer_list<std::string>& path);

std::string secTimeToReadableTime(const long& secTime);

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
