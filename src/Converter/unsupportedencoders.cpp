/* ---------------------------------------------------------------------------
** Author: Martin Geier
** unsupportedencoders.cpp is part of OniboConverter2.
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

#include "unsupportedencoders.h"
#include <iostream>
namespace Converter {


void UnsupportedEncoders::addUnsupportedEncoder(const std::string &name,
		const std::string &, PriorityLevel level){
	encoders.push_back(std::make_pair(name, level));
}
bool UnsupportedEncoders::isEmpty(){
	return encoders.empty();
}

std::list<std::pair<std::string, UnsupportedEncoders::PriorityLevel> > UnsupportedEncoders::getEncoders() const{
	return encoders;
}

} /* namespace Converter */
