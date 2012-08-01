/*
 * encodersettings.cpp
 *
 *  Created on: 1.8.2012
 *      Author: martint
 */

#include "encodersettings.h"

namespace Gui {

EncoderSettings::EncoderSettings(ConverterOptions::OptionsDatabase &database,
		ComboBoxExt<ConverterOptions::Format>& videoFormat,
		ComboBoxExt<ConverterOptions::Encoder>& videoEncoder,
		ComboBoxExt<ConverterOptions::Bitrate>& videoBitrate): database(database),
				videoFormat(videoFormat), videoEncoder(videoEncoder), videoBitrate(videoBitrate){

}

EncoderSettings::~EncoderSettings() {}

void EncoderSettings::videoFormatChanged(){
	ConverterOptions::Format format;
	bool isSet = getActiveFormat(format);
	if(isSet){
		bool isSetOldEncoder = false;
		setVideoEncoders(format.getEncoders().getEncoders(), isSetOldEncoder);
		if(isSetOldEncoder){
			videoBitrate.set_sensitive(true);
		}else{
			videoBitrate.set_sensitive(false);
		}
	}
}

void EncoderSettings::videoEncoderChanged(){
	ConverterOptions::Encoder encoder;
	bool isSet;
	encoder = videoEncoder.get_active_row_item(isSet);
	if(isSet){
		setVideoBitrates(encoder.getBitrates());
	}
}
void EncoderSettings::setSensitive(bool sensitive){
	videoFormat.set_sensitive(sensitive);
	videoEncoder.set_sensitive(sensitive);
	videoBitrate.set_sensitive(sensitive);
}
void EncoderSettings::fillVideoFormats(const std::list<ConverterOptions::Format>& formats){
	bool isSetOldFormat = false;
	setVideoFormats(formats, isSetOldFormat);
	if(isSetOldFormat){
		videoEncoder.set_sensitive(true);
		if(videoEncoder.is_selected()){
			videoBitrate.set_sensitive(true);
		}
	}else{
		videoEncoder.remove_all();
		videoEncoder.set_sensitive(false);
		videoBitrate.remove_all();
		videoBitrate.set_sensitive(false);
	}
}
bool EncoderSettings::isAllSet(std::string& message){
	if (!videoFormat.is_sensitive() || !videoFormat.is_selected()){
		message = "No set video format";
		return false;
	}
	if (!videoEncoder.is_sensitive() || !videoEncoder.is_selected()){
		message = "No set video encoder";
		return false;
	}
	if (!videoBitrate.is_sensitive() || !videoBitrate.is_selected()){
		message = "No set video bitrate";
		return false;
	}
	return true;
}
//================================================
bool EncoderSettings::getActiveFormat(ConverterOptions::Format& activeFormat){
	bool isSelected = false;
	activeFormat = videoFormat.get_active_row_item(isSelected);
	return isSelected;
}
void EncoderSettings::setVideoFormats(const std::list<ConverterOptions::Format>& formats,
		bool& isSetOldFormat){
	std::string oldFormat = "";
	isSetOldFormat = false;
	if(videoFormat.is_selected()){
		oldFormat = videoFormat.get_active_text();
	}
	videoFormat.set_sensitive(true);
	videoFormat.remove_all();
	for(auto formatIter = formats.begin(); formatIter != formats.end(); ++formatIter){
		videoFormat.append(formatIter->getName(), *formatIter);
	}
	if(oldFormat.size() > 0){
		videoFormat.set_active_text(oldFormat);
		isSetOldFormat = (videoFormat.get_active_text() == oldFormat);
	}
}
void EncoderSettings::setVideoEncoders(const std::list<ConverterOptions::Encoder>& encoders,
		bool& isSetOldEncoder){
	isSetOldEncoder = false;
	std::string oldEncoder = "";
	if(videoEncoder.is_selected()){
		oldEncoder = videoEncoder.get_active_text();
	}
	videoEncoder.set_sensitive(true);
	videoEncoder.remove_all();
	for(auto encoderIter = encoders.begin(); encoderIter != encoders.end(); ++encoderIter){
		videoEncoder.append(encoderIter->getName(), *encoderIter);
	}
	if(oldEncoder.size() > 0){
		videoEncoder.set_active_text(oldEncoder);
		isSetOldEncoder = (videoEncoder.get_active_text() == oldEncoder);
	}
}
void EncoderSettings::setVideoBitrates(const ConverterOptions::Bitrates& bitrates){
	videoBitrate.set_sensitive(true);
	for(auto bitratesIter = bitrates.begin(); bitratesIter != bitrates.end(); ++bitratesIter){
		videoBitrate.append(toS(bitratesIter->getValue()), *bitratesIter);
	}
	videoBitrate.set_active_row_number(bitrates.size()/2);
}
} /* namespace Gui */
