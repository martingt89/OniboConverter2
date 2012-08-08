/*
 * encodersettings.cpp
 *
 *  Created on: 1.8.2012
 *      Author: martint
 */

#include "encodersettings.h"
//#include <iostream> //todo remove
namespace Gui {

EncoderSettings::EncoderSettings(ConverterOptions::OptionsDatabase &database,
		ComboBoxExt<ConverterOptions::Format>& videoFormat,
		ComboBoxExt<ConverterOptions::Encoder>& videoEncoder,
		ComboBoxExt<ConverterOptions::Bitrate>& videoBitrate,
		ComboBoxExt<Path>& videoFFpreset): database(database),
				videoFormat(videoFormat), videoEncoder(videoEncoder),
				videoBitrate(videoBitrate), videoFFpreset(videoFFpreset){

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
			enableFFpresetIfSupport();
		}else{
			videoBitrate.set_sensitive(false);
			disableAndClearFFpreset();
		}
	}
}

void EncoderSettings::videoEncoderChanged(){
	ConverterOptions::Encoder encoder;
	bool isSet;
	encoder = videoEncoder.get_active_row_item(isSet);
	if(isSet){
		enableFFpresetIfSupport();
		setVideoBitrates(encoder.getBitrates());
	}
}
void EncoderSettings::setUnsensitive(){
	videoFormat.set_sensitive(false);
	videoEncoder.set_sensitive(false);
	videoBitrate.set_sensitive(false);
	videoFFpreset.set_sensitive(false);
}
void EncoderSettings::fillVideoFormats(const std::list<ConverterOptions::Format>& formats){
	bool isSetOldFormat = false;
	setVideoFormats(formats, isSetOldFormat);
	if(isSetOldFormat){
		videoEncoder.set_sensitive(true);
		if(videoEncoder.is_selected()){
			videoBitrate.set_sensitive(true);
			enableFFpresetIfSupport();
		}
	}else{
		disableAndClearFFpreset();
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
void EncoderSettings::enableFFpresetIfSupport(){
//	std::cout<<__FILE__<<" "<<__LINE__<<std::endl;
	std::pair<std::string, Path> selectedFFpreset;
	bool isSelected = false;
	if(videoFFpreset.is_selected()){
//		std::cout<<__FILE__<<" "<<__LINE__<<std::endl;
		selectedFFpreset.first = videoFFpreset.get_active_text();
		selectedFFpreset.second = videoFFpreset.get_active_row_item(isSelected);
	}
	bool setEncoder = false;
	ConverterOptions::Encoder activeEnc = videoEncoder.get_active_row_item(setEncoder);
	if(setEncoder && activeEnc.hasFFpreset()){
//		std::cout<<__FILE__<<" "<<__LINE__<<std::endl;
		videoFFpreset.remove_all();
		videoFFpreset.set_sensitive(true);
		std::list<std::pair<std::string, std::string> > ffpresets;
		activeEnc.getFFPresets(ffpresets);
		for(auto ffpresetsIter = ffpresets.begin(); ffpresetsIter != ffpresets.end(); ++ffpresetsIter){
			videoFFpreset.append(ffpresetsIter->first, Path(ffpresetsIter->second));
//			std::cout<<__FILE__<<" "<<__LINE__<<std::endl;
		}
		if(isSelected){
			videoFFpreset.set_active_text(selectedFFpreset.first);
//			std::cout<<__FILE__<<" "<<__LINE__<<std::endl;
		}
	}
}
void EncoderSettings::disableAndClearFFpreset(){
	videoFFpreset.remove_all();
	videoFFpreset.set_sensitive(false);
}
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
