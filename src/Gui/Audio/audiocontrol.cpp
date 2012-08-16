/*
 * audiocontrol.cpp
 *
 *  Created on: 11.8.2012
 *      Author: martint
 */

#include "audiocontrol.h"


namespace Gui {
namespace Audio{

static const std::string COPY_MODE = "copy";
static const int COPY_MODE_ID = 0;
static const std::string CUSTOM_MODE = "custom";
static const int CUSTOM_MODE_ID = 1;
static const std::string DISABLE_MODE = "disable";
static const int DISABLE_MODE_ID = 2;
static const std::string ORIGINAL = "--- original ---";

AudioControl::AudioControl(ConverterOptions::OptionsDatabase &database,
		const Glib::RefPtr<Gtk::Builder>& refGlade) : database(database), encoderControl(database, refGlade),
				audioMode(refGlade, "audioMode") , audioSamplerate(refGlade, "audioSamplerate"),
				audioChannels(refGlade, "audioChannels"){

	initAudioMode(audioMode);
	initSamplerate(audioSamplerate);
	initChannels(audioChannels);
	isEnabledSignals = true;

	audioMode.signal_changed().connect(sigc::mem_fun(*this, &AudioControl::audioModeChanged));
	audioSamplerate.signal_changed().connect(sigc::mem_fun(*this, &AudioControl::audioSamplerateChanged));
	audioChannels.signal_changed().connect(sigc::mem_fun(*this, &AudioControl::audioChannelsChanged));
	encoderControl.signalUserInput().connect(sigc::mem_fun(*this, &AudioControl::sendUserInputSignal));
}

AudioControl::~AudioControl() {
	// TODO Auto-generated destructor stub
}

void AudioControl::containerChanged(const ConverterOptions::Container& container){
	audioMode.set_sensitive(true);
	actualContainer = container;

	bool isSelected = audioMode.is_selected();
	bool isEnableAudio = isSelected && (audioMode.get_active_row_item() == CUSTOM_MODE_ID);
	encoderControl.aktualizeSettings(isEnableAudio, container);

	if(isEnableAudio){	//TODO add encoderControl.isFormat
		audioSamplerate.set_sensitive(true);
		audioChannels.set_sensitive(true);
	}else{
		audioSamplerate.set_sensitive(false);
		audioChannels.set_sensitive(false);
	}
}
void AudioControl::saveSettingsState(){
	audioMode.save_actual_state();
	audioSamplerate.save_actual_state();
	audioChannels.save_actual_state();
	encoderControl.saveSettingsState();
}
void AudioControl::restoreSettingsState(){
	isEnabledSignals = false;
	audioMode.restor_saved_state();
	audioSamplerate.restor_saved_state();
	audioChannels.restor_saved_state();
	encoderControl.restoreSettingsState();
	isEnabledSignals = true;
}
bool AudioControl::checkSettingsComplete(std::string& message){
	if(!audioMode.isSelectedActivableRow()){
		message = "Audio mode is not set";
		return false;
	}
	if(audioMode.get_active_row_item() == CUSTOM_MODE_ID){
		if(!audioSamplerate.isSelectedActivableRow()){
			message = "Samplerate is not set";
			return false;
		}
		if(!audioChannels.isSelectedActivableRow()){
			message = "Channel is not set";
			return false;
		}
		if(!encoderControl.checkSettingsComplete(message)){
			return false;
		}
	}
	return true;
}
void AudioControl::disableSettings(){
	audioMode.set_sensitive(false);
	audioSamplerate.set_sensitive(false);
	audioChannels.set_sensitive(false);
	encoderControl.disableSettings();
}
void AudioControl::setActiveProfile(const Profile::Profile& activeProfile){
	//
	int row;
	if(activeProfile.getAudioMode(row)){
		audioMode.set_active_row_number(row);
		if(audioMode.get_active_row_item() == CUSTOM_MODE_ID){
			encoderControl.setActiveProfile(activeProfile);
		}else{
			disableSettings();
		}
	}else{
		audioMode.unset_active();
		disableSettings();
	}
	//
	ConverterOptions::Samplerate samplerate;
	bool isOriginal;
	if(activeProfile.getAudioSamplerate(samplerate, isOriginal)){
		if(isOriginal){
			audioSamplerate.set_active_row_number(0);
		}else{
			audioSamplerate.set_active_text(samplerate.toStr());
		}
	}else{
		audioSamplerate.unset_active();
	}
	//
	ConverterOptions::Channel channel;
	bool isOriginalChannel;
	if(activeProfile.getAudioChannel(channel, isOriginalChannel)){
		if(isOriginalChannel){
			audioChannels.set_active_row_number(0);
		}else{
			audioChannels.set_active_text(channel.toStr());
		}
	}else{
		audioChannels.unset_active();
	}
}
sigc::signal<void>& AudioControl::signalUserInput(){
	return userEvent;
}
void AudioControl::audioModeChanged(){
	if(isEnabledSignals){
		isEnabledSignals = false;
		bool isSelected = audioMode.is_selected();
		bool isEnableAudio = isSelected && (audioMode.get_active_row_item() == CUSTOM_MODE_ID);
		encoderControl.aktualizeSettings(isEnableAudio, actualContainer);
		if(isEnableAudio){
			audioSamplerate.set_sensitive(true);
			audioChannels.set_sensitive(true);
		}else{
			audioSamplerate.set_sensitive(false);
			audioChannels.set_sensitive(false);
		}
		sendUserInputSignal();
		isEnabledSignals = true;
	}
}
void AudioControl::audioSamplerateChanged(){
	if(isEnabledSignals){
		sendUserInputSignal();
	}
}
void AudioControl::audioChannelsChanged(){
	if(isEnabledSignals){
		sendUserInputSignal();
	}
}

void AudioControl::sendUserInputSignal(){
	userEvent();
}

void AudioControl::initAudioMode(ComboBoxExt<int>& audioMode){
	audioMode.append(COPY_MODE, COPY_MODE_ID);
	audioMode.append(CUSTOM_MODE, CUSTOM_MODE_ID);
	audioMode.append(DISABLE_MODE, DISABLE_MODE_ID);
	audioMode.set_active_text(CUSTOM_MODE);
}
void AudioControl::initSamplerate(ComboBoxExt<ConverterOptions::Samplerate>& audioSamplerate){
	audioSamplerate.append(ORIGINAL);
	auto samplerates = database.getSamplerates().getSamplerates();
	std::for_each(samplerates.begin(), samplerates.end(),
			[&audioSamplerate](const ConverterOptions::Samplerate& sample){
		audioSamplerate.append(sample.toStr(), sample);
	});
	if(samplerates.size() > 2){
		audioSamplerate.set_active_row_number(samplerates.size() - 1);
	}else{
		audioSamplerate.set_active_row_number(samplerates.size() / 2);
	}
}
void AudioControl::initChannels(ComboBoxExt<ConverterOptions::Channel>& audioChannels){
	audioChannels.append(ORIGINAL);
	auto channels = database.getChannels();
	std::for_each(channels.begin(), channels.end(),
			[&audioChannels](const ConverterOptions::Channel& channel){
		audioChannels.append(channel.toStr(), channel);
	});
	audioChannels.set_active_row_number(0);
}
}
} /* namespace Gui */
