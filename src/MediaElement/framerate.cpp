/* ---------------------------------------------------------------------------
** Author: Martin Geier
** framerate.cpp is part of OniboConverter2.
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

#include "framerate.h"
#include "../helper.h"

namespace MediaElement {

static const std::string ORIGINAL="--- original ---";

Framerate::Framerate(double framerate) {
	this->framerate = framerate;
}

double Framerate::getValue() const{
	return framerate;
}
std::string Framerate::readableForm() const{
	if(framerate >= 0){
		return toS(framerate);
	}else{
		return ORIGINAL;
	}
}
bool Framerate::isOriginal() const{
	return framerate < 0;
}
void Framerates::addFramerate(const Framerate& framerate){
	framerates.push_back(framerate);
}

std::list<Framerate> Framerates::getFramerats() const{
	return framerates;
}

} /* namespace MediaElement */
