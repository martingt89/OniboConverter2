/* ---------------------------------------------------------------------------
** Author: Martin Geier
** elementsrelations.cpp is part of OniboConverter2.
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

#include "elementsrelations.h"

namespace MediaElement {

std::list<std::string> ElementsRelations::getFormatsByContainer(const Container& container){
	return containerToFormats.get(container);
}
std::list<std::string> ElementsRelations::getAudioEncodersByFormat(const Format& format){
	return formatToEncoders.get(format);
}
std::list<std::string> ElementsRelations::getVideoEncodersByFormat(const Format& format){
	return formatToEncoders.get(format);
}
std::string ElementsRelations::getBitratesByEncoder(const Encoder& encoder){
	return encoderToBitrates.get(encoder);
}
std::string ElementsRelations::getAudioGradesByEncoder(const Encoder& encoder){
	return encoderToAudioGrade.get(encoder);
}
bool ElementsRelations::getFFprefixByEncoder(const Encoder& encoder, std::string& ffprefix){
	bool isExist = false;
	ffprefix = encoderToFFpreset.get(encoder, isExist);
	return isExist;
}
/////////////////////////////////

void ElementsRelations::setContainerToFormats(const Container& container,
		const std::list<std::string>& formatsNames){
	containerToFormats.set(container, formatsNames);
}
void ElementsRelations::setFormatToEncoder(const Format& format, const std::list<std::string>& encodersNames){
	formatToEncoders.set(format, encodersNames);
}
void ElementsRelations::setEncoderToBitrates(const Encoder& encoder, const std::string& bitratesName){
	encoderToBitrates.set(encoder, bitratesName);
}
void ElementsRelations::setEncoderToAudioGrade(const Encoder& encoder, const std::string& audioGradeName){
	encoderToAudioGrade.set(encoder, audioGradeName);
}
void ElementsRelations::setEncoderToFFpreset(const Encoder& encoder, const std::string& ffpresetName){
	encoderToFFpreset.set(encoder, ffpresetName);
}
} /* namespace MediaElement */
