/*
 * encodersettings.h
 *
 *  Created on: 1.8.2012
 *      Author: martint
 */

#ifndef ENCODERSETTINGS_H_
#define ENCODERSETTINGS_H_

#include "../../ConverterOptions/optionsdatabase.h"
#include "../comboboxext.h"

namespace Gui {

class EncoderSettings {
public:
	EncoderSettings(ConverterOptions::OptionsDatabase &database,
			ComboBoxExt<ConverterOptions::Format>& videoFormat,
			ComboBoxExt<ConverterOptions::Encoder>& videoEncoder,
			ComboBoxExt<ConverterOptions::Bitrate>& videoBitrate);
	virtual ~EncoderSettings();

	void videoFormatChanged();
	void videoEncoderChanged();
	void fillVideoFormats(const std::list<ConverterOptions::Format>& formats);
	void setSensitive(bool sensitive);
	bool isAllSet(std::string& message);
private:
	bool getActiveFormat(ConverterOptions::Format& activeFormat);
	void setVideoFormats(const std::list<ConverterOptions::Format>& formats, bool& isSetOldFormat);
	void setVideoEncoders(const std::list<ConverterOptions::Encoder>& encoders,	bool& isSetOldEncoder);
	void setVideoBitrates(const ConverterOptions::Bitrates& bitrates);
	ConverterOptions::OptionsDatabase &database;
	ComboBoxExt<ConverterOptions::Format>& videoFormat;
	ComboBoxExt<ConverterOptions::Encoder>& videoEncoder;
	ComboBoxExt<ConverterOptions::Bitrate>& videoBitrate;
};

} /* namespace Gui */
#endif /* ENCODERSETTINGS_H_ */
