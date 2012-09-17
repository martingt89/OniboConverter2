/* ---------------------------------------------------------------------------
** Author: Martin Geier
** samplerate.cpp is part of OniboConverter2.
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

#include "samplerate.h"
#include "../helper.h"

namespace MediaElement {

static const std::string ORIGINAL="--- original ---";

Samplerate::Samplerate(){
	samplerate = 0;
}

Samplerate::Samplerate(int samplerate) {
	this->samplerate = samplerate;
}

int Samplerate::getValue() const{
	return samplerate;
}
std::string Samplerate::readableForm() const{
	if(samplerate >= 0){
		return toS(samplerate);
	}
	return ORIGINAL;
}
bool Samplerate::isOriginal() const{
	return samplerate < 0;
}
//=================================================================================================
void Samplerates::addSamplerate(const Samplerate& samplerate){
	samplerates.push_back(samplerate);
}
std::list<Samplerate> Samplerates::getSamplerates() const{
	return samplerates;
}


} /* namespace MediaElement */
