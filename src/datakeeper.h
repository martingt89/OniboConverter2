/*
 * datakeeper.h
 *
 *  Created on: 13.7.2012
 *      Author: martint
 */

#ifndef DATAKEEPER_H_
#define DATAKEEPER_H_

#include "AVBox/avbox.h"
#include "AVBox/guisettings.h"
#include "AVBox/formattoencoders.h"
#include "AVBox/supportedencoders.h"

class DataKeeper {
public:
	DataKeeper(AVBox::AVBox audioVideoData,
			AVBox::GuiSettings guiData,
			AVBox::FormatToEncoders convert,
			AVBox::SupportedEncoders suportedEncoders);
	AVBox::AVBox* getAVBox();
	AVBox::GuiSettings* getGuiSettings();
	AVBox::FormatToEncoders* getFormatToEncoders();
	AVBox::SupportedEncoders* getSupportedEncoders();
private:
	AVBox::AVBox audioVideoData;
	AVBox::GuiSettings guiData;
	AVBox::FormatToEncoders convert;
	AVBox::SupportedEncoders suportedEncoders;
};

#endif /* DATAKEEPER_H_ */
