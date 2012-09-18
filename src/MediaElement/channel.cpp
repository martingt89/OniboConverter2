/* ---------------------------------------------------------------------------
** Author: Martin Geier
** channel.cpp is part of OniboConverter2.
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

#include "channel.h"
#include "../helper.h"

namespace MediaElement {

static const std::string ORIGINAL="--- original ---";

Channel::Channel() {
	name = "";
	value = -1;
}
Channel::Channel(const std::string& name, const int& value){
	this->name = name;
	this->value = value;
}
Channel::~Channel() {

}
int Channel::getValue() const{
	return value;
}
//std::string Channel::toStr() const{
//	if(value < 0){
//		return ORIGINAL;
//	}
//	if(name.size() >= 0){
//		return name;
//	}
//	return toS(value);
//}
std::string Channel::readableForm() const{
	if(value < 0){
		return ORIGINAL;
	}
	if(name.size() > 0){
		return name;
	}
	return toS(value);
}
//Converter::ConvertSettingsList Channel::getConvertArguments() const{
//	Converter::ConvertSettingsList args;
//	if(value >= 0){
//		Converter::ConvertSettings arg(Converter::ConvertSettings::CHANNELS);		//-ac
//		arg.addValue(toS(value));
//		args.add(arg);
//	}
//	return args;
//}
std::string Channel::getName() const{
	return name;
}
bool Channel::isOriginal() const{
	return value < 0;
}
} /* namespace MediaElement */
