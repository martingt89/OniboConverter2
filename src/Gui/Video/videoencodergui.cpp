/*
 * videoencodergui.cpp
 *
 *  Created on: 8.8.2012
 *      Author: martint
 */

#include "videoencodergui.h"
#include "../../helper.h"

namespace Gui {

VideoEncoderGui::VideoEncoderGui(ConverterOptions::OptionsDatabase &database,
		const Glib::RefPtr<Gtk::Builder>& refGlade) : database(database),
				videoFormat(refGlade, "videoFormat"), videoEncoder(refGlade, "videoEncoder"),
				videoBitrate(refGlade, "videoBitrate"), videoFFpreset(refGlade, "videoFFpreset"){
	isEnableSignals = true;
	videoFormat.signal_changed().connect(sigc::mem_fun(*this, &VideoEncoderGui::videoFormatChanget));
	videoEncoder.signal_changed().connect(sigc::mem_fun(*this, &VideoEncoderGui::videoEncoderChanget));
	videoBitrate.signal_changed().connect(sigc::mem_fun(*this, &VideoEncoderGui::videoBitrateChanget));
	videoFFpreset.signal_changed().connect(sigc::mem_fun(*this, &VideoEncoderGui::videoFFpresetChanget));
}

VideoEncoderGui::~VideoEncoderGui() {}

void VideoEncoderGui::aktualizeSettings(const bool& isVideoActive,
		const ConverterOptions::Container& container){
	isEnableSignals = false;
	if(isVideoActive){
		setFormatsFromContainer(container);
		aktualizeEncoder();
		aktualizeBitrate();
		aktualizeFFpreset();
	}else{
		videoFormat.set_sensitive(false);
		videoEncoder.set_sensitive(false);
		videoBitrate.set_sensitive(false);
		videoFFpreset.set_sensitive(false);
	}
	isEnableSignals = true;
}
void VideoEncoderGui::disableSettings(){
	videoFormat.set_sensitive(false);
	videoEncoder.set_sensitive(false);
	videoBitrate.set_sensitive(false);
	videoFFpreset.set_sensitive(false);
}
void VideoEncoderGui::videoFormatChanget(){
	if(isEnableSignals){
		isEnableSignals = false;
		aktualizeEncoder();
		aktualizeBitrate();
		aktualizeFFpreset();
		isEnableSignals = true;
		sendUserInputSignal();
	}
}
void VideoEncoderGui::saveSettingsState(){
	videoFormat.save_actual_state();
	videoEncoder.save_actual_state();
	videoBitrate.save_actual_state();
	videoFFpreset.save_actual_state();
}
void VideoEncoderGui::restoreSettingsState(){
	videoFormat.restor_saved_state();
	videoEncoder.restor_saved_state();
	videoBitrate.restor_saved_state();
	videoFFpreset.restor_saved_state();
}
void VideoEncoderGui::videoEncoderChanget(){
	if(isEnableSignals){
		isEnableSignals = false;
		aktualizeBitrate();
		aktualizeFFpreset();
		isEnableSignals = true;
		sendUserInputSignal();
	}
}

void VideoEncoderGui::videoBitrateChanget(){
	if(isEnableSignals){
		isEnableSignals = false;
		aktualizeFFpreset();
		isEnableSignals = true;
		sendUserInputSignal();
	}
}

void VideoEncoderGui::videoFFpresetChanget(){
	if(isEnableSignals){
		sendUserInputSignal();
	}
}

void VideoEncoderGui::setFormatsFromContainer(const ConverterOptions::Container& container){
	bool isSet = videoFormat.isSet();
	std::string actualFormat = "";
	if(isSet){
		actualFormat = videoFormat.get_active_text();
	}

	videoFormat.remove_all();
	videoFormat.set_sensitive(true);

	auto formats = container.getFormats().getVideoFormatsList();

	std::for_each(formats.begin(), formats.end(), [&](const ConverterOptions::Format& format){
		videoFormat.append(format.getName(), format);
	});
	if(isSet){
		videoFormat.set_active_text(actualFormat);
	}
}
void VideoEncoderGui::aktualizeEncoder(){
	if(!videoFormat.isSetSensitiveRow()){
		videoEncoder.set_sensitive(false);
		return;
	}
	bool isSet = videoEncoder.is_selected();
	std::string actualEncoder = "";
	if(isSet){
		actualEncoder = videoEncoder.get_active_text();
	}
	videoEncoder.set_sensitive(true);
	videoEncoder.remove_all();
	auto actualFormat = videoFormat.get_active_row_item();
	auto encodersList = actualFormat.getEncoders().getEncoders();
	std::for_each(encodersList.begin(), encodersList.end(), [&](const ConverterOptions::Encoder& encoder){
		videoEncoder.append(encoder.getName(), encoder);
	});
	if(isSet){
		videoEncoder.set_active_text(actualEncoder);
	}
}

void VideoEncoderGui::aktualizeBitrate(){
	if(!videoEncoder.isSetSensitiveRow()){
		videoBitrate.set_sensitive(false);
		return;
	}
	bool isSetBitrate = videoBitrate.is_selected();
	std::string actualBitrate = "";
	if(isSetBitrate){
		actualBitrate = videoBitrate.get_active_text();
	}
	videoBitrate.set_sensitive(true);
	videoBitrate.remove_all();
	auto actualEncoder = videoEncoder.get_active_row_item();
	auto bitratesList = actualEncoder.getBitrates();
	std::for_each(bitratesList.begin(), bitratesList.end(), [&](const ConverterOptions::Bitrate& bitrate){
		videoBitrate.append(toS(bitrate.getValue()), bitrate);
	});
	if(isSetBitrate){
		videoBitrate.set_active_text(actualBitrate);
	}
}

void VideoEncoderGui::aktualizeFFpreset(){
	if(!videoEncoder.isSetSensitiveRow() || !videoEncoder.get_active_row_item().hasFFpreset()){
		videoFFpreset.set_sensitive(false);
		return;
	}
	bool isSetFFpreset = videoFFpreset.is_selected();
	std::string actualFFpreset = "";
	if(isSetFFpreset){
		actualFFpreset = videoFFpreset.get_active_text();
	}
	videoFFpreset.set_sensitive(true);
	videoFFpreset.remove_all();
	std::list<std::pair<std::string, std::string> > ffpresets;
	videoEncoder.get_active_row_item().getFFPresets(ffpresets);

	std::for_each(ffpresets.begin(), ffpresets.end(),
			[&](const std::pair<std::string, std::string>& ffpreset){
		videoFFpreset.append(ffpreset.first, Path(ffpreset.second));
	});
	if(isSetFFpreset){
		videoFFpreset.set_active_text(actualFFpreset);
	}
}

void VideoEncoderGui::sendUserInputSignal(){

}

} /* namespace Gui */
