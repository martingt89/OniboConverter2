/*
 * elementsrelations.cpp
 *
 *  Created on: 9.9.2012
 *      Author: martin
 */

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
