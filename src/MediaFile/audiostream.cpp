/* ---------------------------------------------------------------------------
** Author: Martin Geier
** audiostream.cpp is part of OniboConverter2.
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

#include "audiostream.h"

namespace MediaFile {

AudioStream::AudioStream(int firstNumber, int secondNumber, std::string id, std::string language) :
		Stream(firstNumber,secondNumber, id, language){

}

AudioStream::~AudioStream(){

}

void AudioStream::setValue(const Audio& name, const std::string& value){
	content.set(name, value);
}

bool AudioStream::getValue(const Audio& name, std::string& value) const{
	bool isExistParameter = false;
	value = content.get(name, isExistParameter);
	return isExistParameter;
}

int AudioStream::priority() const{
	std::string chan = content.get(CHANNELS);
	if(chan == "mono"){
		return 1;
	}
	if(chan == "stereo"){
		return 2;
	}
	if(chan == "5.1"){
		return 6;
	}
	if(chan == "7.1"){
		return 8;
	}
	return 0;
}

} /* namespace MediaFile */
