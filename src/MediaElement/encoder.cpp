/* ---------------------------------------------------------------------------
** Author: Martin Geier
** encoder.cpp is part of OniboConverter2.
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

#include "encoder.h"
#include "ffpreset.h"
#include "../helper.h"

namespace MediaElement {

Encoder::Encoder(){
	this->name = "";
	this->description = "";
	enableMultithread = false;
}
Encoder::Encoder(std::string name, std::string description, bool isEnableMultithread) {
	this->name = name;
	this->description = description;
	enableMultithread = isEnableMultithread;
}
std::string Encoder::getName() const{
	return name;
}
std::string Encoder::getDescription() const{
	return description;
}
std::string Encoder::readableForm() const{
	return getName();
}
bool Encoder::operator<(const Encoder& second) const{
	return this->name < second.name;
}
bool Encoder::operator==(const Encoder& second) const{
	return this->name == second.name;
}
bool Encoder::isSupportedThreading() const{
	return enableMultithread;
}
//=======================================================================
void Encoders::addEncoder(const Encoder& encoder){
	encoders.set(encoder.getName(), encoder);
}
std::list<Encoder> Encoders::getEncoders() const{
	return encoders.getListOfValues();
}
Encoder Encoders::getEncoderByName(const std::string& encoderName) const{
	bool isExist = false;
	Encoder enc = encoders.get(encoderName, isExist);
	assert(isExist, "Encoder name doesn't exist: "+encoderName);
	return enc;
}
bool Encoders::getEncoderByName(const std::string& encoderName, Encoder& encoder) const{
	bool isExist = false;
	encoder = encoders.get(encoderName, isExist);
	return isExist;
}

} /* namespace MediaElement */
