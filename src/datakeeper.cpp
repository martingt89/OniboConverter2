/*
 * datakeeper.cpp
 *
 *  Created on: 13.7.2012
 *      Author: martint
 */

#include "datakeeper.h"


DataKeeper::DataKeeper(AVBox::AVBox audioVideoData,
		AVBox::GuiSettings guiData,
		AVBox::FormatToEncoders convert,
		AVBox::SupportedEncoders suportedEncoders) :
		audioVideoData(audioVideoData), guiData(guiData),
		convert(convert), suportedEncoders(suportedEncoders){
}

AVBox::AVBox* DataKeeper::getAVBox(){
	return &audioVideoData;
}
AVBox::GuiSettings* DataKeeper::getGuiSettings(){
	return &guiData;
}
AVBox::FormatToEncoders* DataKeeper::getFormatToEncoders(){
	return &convert;
}
AVBox::SupportedEncoders* DataKeeper::getSupportedEncoders(){
	return &suportedEncoders;
}
