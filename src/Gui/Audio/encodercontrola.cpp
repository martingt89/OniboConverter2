/*
 * encodercontrol.cpp
 *
 *  Created on: 11.8.2012
 *      Author: martint
 */

#include "encodercontrola.h"
#include <iostream>

namespace Gui {
namespace Audio {
EncoderControlA::EncoderControlA(ConverterOptions::OptionsDatabase &database,
		const Glib::RefPtr<Gtk::Builder>& refGlade) : database(database),
				audioFormat(refGlade, "audioFormat"), audioEncoder(refGlade, "audioEncoder"),
				audioBitrate(refGlade, "audioBitrate"){
	isEnableSignals = true;
	isUserInput = true;
	audioFormat.signal_changed().connect(sigc::mem_fun(*this, &EncoderControlA::audioFormatChanged));
	audioEncoder.signal_changed().connect(sigc::mem_fun(*this, &EncoderControlA::audioEncoderChanged));
	audioBitrate.signal_changed().connect(sigc::mem_fun(*this, &EncoderControlA::audioBitrateChanged));
}

EncoderControlA::~EncoderControlA() {}

void EncoderControlA::aktualizeSettings(const bool& isAudioActive,
		const ConverterOptions::Container& container){
	isEnableSignals = false;
	if(isAudioActive){
		setFormatsFromContainer(container);
		aktualizeEncoder();
		aktualizeBitrate();
	}else{
		audioFormat.set_sensitive(false);
		audioEncoder.set_sensitive(false);
		audioBitrate.set_sensitive(false);
	}
	isEnableSignals = true;
}
void EncoderControlA::disableSettings(){
	audioFormat.set_sensitive(false);
	audioEncoder.set_sensitive(false);
	audioBitrate.set_sensitive(false);
}
void EncoderControlA::saveSettingsState(){
	audioFormat.save_actual_state();
	audioEncoder.save_actual_state();
	audioBitrate.save_actual_state();
}
void EncoderControlA::restoreSettingsState(){
	isEnableSignals = false;
	audioFormat.restor_saved_state();
	audioEncoder.restor_saved_state();
	audioBitrate.restor_saved_state();
	isEnableSignals = true;
}
sigc::signal<void>& EncoderControlA::signalUserInput(){
	return userEvent;
}
bool EncoderControlA::checkSettingsComplete(std::string& message){
	if(!audioFormat.isSelectedActivableRow()){
		message = "Audio format is not set";
		return false;
	}
	if(!audioEncoder.isSelectedActivableRow()){
		message = "Audio encoder is not set";
		return false;
	}
	if(!audioBitrate.isSelectedActivableRow()){
		message = "Audio bitrate is not set";
		return false;
	}
	return true;
}
void EncoderControlA::setActiveProfile(const Profile::Profile& activeProfile){
	std::string formatName;
	if(activeProfile.getAudioFormatName(formatName)){
		audioFormat.set_active_text(formatName);
		std::string encoderName;
		if(activeProfile.getAudioEncoderName(encoderName)){
			audioEncoder.set_active_text(encoderName);
			ConverterOptions::Bitrate bitrate;
			if(activeProfile.getAudioBitrate(bitrate)){
				audioBitrate.set_active_text(bitrate.toStr());
			}else{
				audioBitrate.unset_active();
			}
		}else{
			audioEncoder.unset_active();
		}
	}else{
		audioFormat.unset_active();
	}
}
Converter::ConvertSettingsList EncoderControlA::getConvertArguments() const{
	Converter::ConvertSettingsList args;
	args.add(audioEncoder.get_active_row_item().getConvertArguments());
	args.add(audioBitrate.get_active_row_item().getConvertArguments());
	return args;
}
void EncoderControlA::audioFormatChanged(){
	if(isEnableSignals){
		isEnableSignals = false;
		aktualizeEncoder();
		aktualizeBitrate();
		isEnableSignals = true;
		sendUserInputSignal();
	}
}
void EncoderControlA::audioEncoderChanged(){
	if(isEnableSignals){
		isEnableSignals = false;
		aktualizeBitrate();
		isEnableSignals = true;
		sendUserInputSignal();
	}
}
void EncoderControlA::audioBitrateChanged(){
	if(isEnableSignals){
		sendUserInputSignal();
	}
}
void EncoderControlA::setFormatsFromContainer(const ConverterOptions::Container& container){
	bool isSet = audioFormat.is_selected();
	std::string actualFormat = "-";
	if(isSet){
		actualFormat = audioFormat.get_active_text();
	}

	audioFormat.remove_all();
	audioFormat.set_sensitive(true);

	auto formats = container.getFormats().getAudioFormatsList();

	if(formats.size() == 0){
		this->disableSettings();
		return;
	}

	std::for_each(formats.begin(), formats.end(), [&](const ConverterOptions::Format& format){
		audioFormat.append(format.getName(), format);
	});
	if(isSet){
		audioFormat.set_active_text(actualFormat);
	}
	if(audioFormat.get_active_text() != actualFormat){
		audioFormat.set_active_row_number(0);
	}
}
void EncoderControlA::aktualizeEncoder(){
	if(!audioFormat.isSelectedActivableRow()){
		audioEncoder.set_sensitive(false);
		return;
	}
	bool isSet = audioEncoder.is_selected();
	std::string actualEncoder = "-";
	if(isSet){
		actualEncoder = audioEncoder.get_active_text();
	}
	audioEncoder.set_sensitive(true);
	audioEncoder.remove_all();
	auto actualFormat = audioFormat.get_active_row_item();
	auto encodersList = actualFormat.getEncoders().getEncoders();
	std::for_each(encodersList.begin(), encodersList.end(), [&](const ConverterOptions::Encoder& encoder){
		audioEncoder.append(encoder.getName(), encoder);
	});
	if(isSet){
		audioEncoder.set_active_text(actualEncoder);
	}
	if(audioEncoder.get_active_text() != actualEncoder && encodersList.size() > 0){
		audioEncoder.set_active_row_number(0);
	}
	if(encodersList.size() == 0){
		audioEncoder.set_sensitive(false);	//todo text "no supported encoder"
	}
}
void EncoderControlA::aktualizeBitrate(){
	if(!audioEncoder.isSelectedActivableRow()){
		audioBitrate.set_sensitive(false);
		return;
	}
	bool isSetBitrate = audioBitrate.is_selected();
	std::string actualBitrate = "";
	if(isSetBitrate){
		actualBitrate = audioBitrate.get_active_text();
	}
	audioBitrate.set_sensitive(true);
	audioBitrate.remove_all();
	auto actualEncoder = audioEncoder.get_active_row_item();
	auto bitratesList = actualEncoder.getBitrates();
	auto userBitrateList = database.getUserVideoBitrate();
	std::copy(userBitrateList.begin(), userBitrateList.end(), std::back_inserter(bitratesList));
	std::for_each(bitratesList.begin(), bitratesList.end(), [&](const ConverterOptions::Bitrate& bitrate){
		audioBitrate.append(bitrate.toStr(), bitrate);
	});
	if(isSetBitrate){
		audioBitrate.set_active_text(actualBitrate);
	}else{
		audioBitrate.set_active_row_number(bitratesList.size() / 2);
	}
}
void EncoderControlA::sendUserInputSignal(){
	if(isUserInput){
		userEvent();
	}
}
}
} /* namespace Gui */
