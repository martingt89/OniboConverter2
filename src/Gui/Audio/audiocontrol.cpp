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

AudioControl::~AudioControl() {}

void AudioControl::containerChanged(const ConverterOptions::Container& container){
	audioMode.set_sensitive(true);
	actualContainer = container;

	bool isSelected = audioMode.is_selected();
	bool isEnableAudio = isSelected && (audioMode.get_active_row_item() == CUSTOM_MODE_ID);
	encoderControl.aktualizeSettings(isEnableAudio, container);

	if(isEnableAudio){	//add encoderControl.isFormat - callback
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
			audioMode.set_sensitive(true);
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
void AudioControl::getNewProfile(Profile::Profile& newProfile){
	//audio mode
	newProfile.addProperty(Profile::Profile::AUDIO_MODE_OPT, toS(audioMode.get_active_row_number()));
	if(audioMode.get_active_row_item() == CUSTOM_MODE_ID){
		encoderControl.getNewProfile(newProfile);
	}
	//audio samplerate
	if(audioSamplerate.isSelectedActivableRow()){
	newProfile.addProperty(Profile::Profile::AUDIO_SAMPLERATE_OPT,
			toS(audioSamplerate.get_active_row_item().getValue()));
	}
	//audio channels
	if(audioChannels.isSelectedActivableRow()){
		newProfile.addProperty(Profile::Profile::AUDIO_CHANNEL_NAME_OPT,
				audioChannels.get_active_row_item().getName());
		newProfile.addProperty(Profile::Profile::AUDIO_CHANNEL_VALUE_OPT,
				toS(audioChannels.get_active_row_item().getValue()));
	}
}
Converter::ConvertSettingsList AudioControl::getConvertArguments() const{
	Converter::ConvertSettingsList args;
	if(audioMode.get_active_row_item() == CUSTOM_MODE_ID){
		args.add(audioChannels.get_active_row_item().getConvertArguments());
		args.add(audioSamplerate.get_active_row_item().getConvertArguments());
		args.add(encoderControl.getConvertArguments());
	}else if(audioMode.get_active_row_item() == COPY_MODE_ID){
		Converter::ConvertSettings arg(Converter::ConvertSettings::ACODEC);	//-acodec
		arg.addValue("copy");
		args.add(arg);
	}else if(audioMode.get_active_row_item() == DISABLE_MODE_ID){
		Converter::ConvertSettings arg(Converter::ConvertSettings::NOAUDIO);		//-an
		args.add(arg);
	}
	return args;
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
	auto samplerates = database.getSamplerates().getSamplerates();
	std::for_each(samplerates.begin(), samplerates.end(),
			[&audioSamplerate](const ConverterOptions::Samplerate& sample){
		audioSamplerate.append(sample.toStr(), sample);
	});
	if(samplerates.size() > 2){
		audioSamplerate.set_active_row_number(samplerates.size() - 2);
	}else{
		audioSamplerate.set_active_row_number(samplerates.size() / 2);
	}
}
void AudioControl::initChannels(ComboBoxExt<ConverterOptions::Channel>& audioChannels){
	auto channels = database.getChannels();
	std::for_each(channels.begin(), channels.end(),
			[&audioChannels](const ConverterOptions::Channel& channel){
		audioChannels.append(channel.toStr(), channel);
	});
	audioChannels.set_active_row_number(0);
}
}
} /* namespace Gui */
