/* ---------------------------------------------------------------------------
** Author: Martin Geier
** logger.cpp is part of OniboConverter2.
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

#include "logger.h"
#include <iostream>

namespace CppExtension {

Logger* Logger::instance = 0;

Logger::Logger() {}

Logger::~Logger() {}

Logger* Logger::getInstance(){
	if(instance == 0){
		instance = new Logger();
	}
	return instance;
}
void Logger::log(LogLevel level, std::string message, std::string fileName, int fileLine, std::string compileTime){
	std::cerr<<"Level: '"<<level<<"' file: '"<<fileName<<"' line: '"<<fileLine<<"' compile time: '"<<compileTime<<std::endl;
	std::cerr<<"\t"<<message<<std::endl;
}

} /* namespace CppExtension */
