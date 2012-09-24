/* ---------------------------------------------------------------------------
** Author: Martin Geier
** audiocontrol.cpp is part of OniboConverter2.
**
** OniboConverter2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
** -------------------------------------------------------------------------*/

#include "audiocontrol.h"


namespace Gui {
namespace Audio{

static const std::string COPY_MODE = "copy";
static const int COPY_MODE_ID = 0;
static const std::string CUSTOM_MODE = "custom";
static const int CUSTOM_MODE_ID = 1;
static const std::string DISABLE_MODE = "disable";
static const int DISABLE_MODE_ID = 2;

AudioControl::AudioControl(MediaElement::ElementsDB& elementsDB,
		const Glib::RefPtr<Gtk::Builder>& refGlade) : elementsDB(elementsDB),
				encoderControl(elementsDB, refGlade),
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

void AudioControl::containerChanged(const MediaElement::Container& container){
	audioMode.set_sensitive(true);
	actualContainer = container;

	bool isSelected = audioMode.isNotDefaultLine();
	bool isEnableAudio = isSelected && (audioMode.getActiveItem() == CUSTOM_MODE_ID);
	encoderControl.aktualizeSettings(isEnableAudio, container);

	if(isEnableAudio){	//todo add encoderControl.isFormat - callback
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
	if(!audioMode.isSensitiveAndNotDefault()){
		message = "Audio mode is not set";
		return false;
	}
	if(audioMode.getActiveItem() == CUSTOM_MODE_ID){
		if(!audioSamplerate.isSensitiveAndNotDefault()){
			message = "Samplerate is not set";
			return false;
		}
		if(!audioChannels.isSensitiveAndNotDefault()){
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
		audioMode.setActiveRowNumber(row);
		if(audioMode.getActiveItem() == CUSTOM_MODE_ID){
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
	MediaElement::Samplerate samplerate;
	if(activeProfile.getAudioSamplerate(samplerate)){
		if(samplerate.isOriginal()){
			audioSamplerate.setActiveRowNumber(0);
		}else{
			audioSamplerate.setActiveText(samplerate.readableForm());
		}
	}else{
		audioSamplerate.unset_active();
	}
	//
	MediaElement::Channel channel;
	if(activeProfile.getAudioChannel(channel)){
		if(channel.isOriginal()){
			audioChannels.setActiveRowNumber(0);
		}else{
			audioChannels.setActiveText(channel.readableForm());
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
	newProfile.setAudioMode(audioMode.getActiveRowNumber());

	if(audioMode.getActiveItem() == CUSTOM_MODE_ID){
		encoderControl.getNewProfile(newProfile);
	}
	//audio samplerate
	if(audioSamplerate.isSensitiveAndNotDefault()){
		newProfile.setAudioSamplerate(audioSamplerate.getActiveItem());
	}

	//audio channels
	if(audioChannels.isSensitiveAndNotDefault()){
		newProfile.setAudioChannel(audioChannels.getActiveItem());
	}
}
void AudioControl::audioModeChanged(){
	if(isEnabledSignals){
		isEnabledSignals = false;
		bool isSelected = audioMode.isNotDefaultLine();
		bool isEnableAudio = isSelected && (audioMode.getActiveItem() == CUSTOM_MODE_ID);
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
	audioMode.setActiveText(CUSTOM_MODE);
}
void AudioControl::initSamplerate(ComboBoxExt<MediaElement::Samplerate>& audioSamplerate){
	auto samplerates = elementsDB.getSamplerates().getSamplerates();
	for(auto sample : samplerates){
		audioSamplerate.append(sample.readableForm(), sample);
	}

	if(samplerates.size() > 2){
		audioSamplerate.setActiveRowNumber(samplerates.size() - 2);
	}else{
		audioSamplerate.setActiveRowNumber(samplerates.size() / 2);
	}
}
void AudioControl::initChannels(ComboBoxExt<MediaElement::Channel>& audioChannels){
	auto channels = elementsDB.getChannels();
	for(auto channel : channels){
		audioChannels.append(channel.readableForm(), channel);
	}
	audioChannels.setActiveRowNumber(0);
}

} /* namespace Audio */
} /* namespace Gui */
