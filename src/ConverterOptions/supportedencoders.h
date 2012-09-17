/* ---------------------------------------------------------------------------
** Author: Martin Geier
** supportedencoders.h is part of OniboConverter2.
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

#ifndef SUPPORTEDENCODERS_H_
#define SUPPORTEDENCODERS_H_

#include "../CppExtension/hashmap.h"
#include <string>

namespace ConverterOptions {

class SupportedEncoders {
public:
	void addEncoder(const std::string& encoderName, const std::string& description);
	bool isSupported(const std::string& encoderName) const;
	std::string getEncoderDescription(const std::string& encoderName) const;
private:
	CppExtension::HashMap<std::string, std::string> encoderNameToDescr;
};

} /* namespace ConverterOptions */
#endif /* SUPPORTEDENCODERS_H_ */
