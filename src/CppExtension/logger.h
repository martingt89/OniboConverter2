/* ---------------------------------------------------------------------------
** Author: Martin Geier
** logger.h is part of OniboConverter2.
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

#ifndef LOGGER_H_
#define LOGGER_H_

#include "../helper.h"

#define easylog(logLevel, message) CppExtension::Logger::getInstance()->\
	log((logLevel), toS(message), __FILE__, __LINE__, __TIME__)

namespace CppExtension {

class Logger {
public:
	enum LogLevel{
		DEDUG, WARNING, ERROR, FATAL
	};
	virtual ~Logger();
	static Logger* getInstance();
	void log(LogLevel level, std::string message, std::string fileName, int fileLine, std::string compileTime);
private:
	Logger();
	Logger(const Logger&);
	const Logger& operator=(const Logger&);
	static Logger* instance;
};

} /* namespace CppExtension */
#endif /* LOGGER_H_ */
