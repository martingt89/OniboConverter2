/* ---------------------------------------------------------------------------
** Author: Martin Geier
** encodercontrola.cpp is part of OniboConverter2.
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

#include "encodercontrola.h"

namespace Gui {
namespace Audio {

static const std::string NO_SUPPORTED_ENCODERS = "no supported encoders";

EncoderControlA::EncoderControlA(MediaElement::ElementsDB& elementsDB,
		const Glib::RefPtr<Gtk::Builder>& refGlade) : elementsDB(elementsDB),
				audioFormat(refGlade, "audioFormat"), audioEncoder(refGlade, "audioEncoder"),
				audioGradeChooser(refGlade, "audioGrade"){
	isEnableSignals = true;
	isUserInput = true;
	audioFormat.signal_changed().connect(sigc::mem_fun(*this, &EncoderControlA::audioFormatChanged));
	audioEncoder.signal_changed().connect(sigc::mem_fun(*this, &EncoderControlA::audioEncoderChanged));
	audioGradeChooser.signal_changed().connect(sigc::mem_fun(*this, &EncoderControlA::audioBitrateChanged));
}

EncoderControlA::~EncoderControlA() {}

void EncoderControlA::aktualizeSettings(const bool& isAudioActive,
		const MediaElement::Container& container){
	isEnableSignals = false;
	if(isAudioActive){
		setFormatsFromContainer(container);
		aktualizeEncoder();
		aktualizeBitrate();
	}else{
		audioFormat.set_sensitive(false);
		audioEncoder.set_sensitive(false);
		audioGradeChooser.set_sensitive(false);
	}
	isEnableSignals = true;
}
void EncoderControlA::disableSettings(){
	audioFormat.set_sensitive(false);
	audioEncoder.set_sensitive(false);
	audioGradeChooser.set_sensitive(false);
}
void EncoderControlA::saveSettingsState(){
	audioFormat.save_actual_state();
	audioEncoder.save_actual_state();
	audioGradeChooser.save_actual_state();
}
void EncoderControlA::restoreSettingsState(){
	isEnableSignals = false;
	audioFormat.restor_saved_state();
	audioEncoder.restor_saved_state();
	audioGradeChooser.restor_saved_state();
	isEnableSignals = true;
}
sigc::signal<void>& EncoderControlA::signalUserInput(){
	return userEvent;
}
bool EncoderControlA::checkSettingsComplete(std::string& message){
	if(!audioFormat.isSensitiveAndNotDefault()){
		message = "Audio format is not set";
		return false;
	}
	if(!audioEncoder.isSensitiveAndNotDefault()){
		message = "Audio encoder is not set";
		return false;
	}
	if(!audioGradeChooser.isSensitiveAndNotDefault()){
		message = "Audio grade is not set";
		return false;
	}
	return true;
}
void EncoderControlA::setActiveProfile(const Profile::Profile& activeProfile){
	MediaElement::Format format;
	if(activeProfile.getAudioFormat(format)){
		audioFormat.setActiveText(format.readableForm());
		MediaElement::Encoder encoder;
		if(activeProfile.getAudioEncoder(encoder)){
			audioEncoder.setActiveText(encoder.readableForm());
			MediaElement::AudioGrade audioGrade;
			if(activeProfile.getAudioGrade(audioGrade)){
				audioGradeChooser.setActiveText(audioGrade.readableForm());
			}else{
				audioGradeChooser.unset_active();
			}
		}else{
			audioEncoder.unset_active();
		}
	}else{
		audioFormat.unset_active();
	}
}
void EncoderControlA::getNewProfile(Profile::Profile& newProfile){
	bool format = false;
	if(audioFormat.isSensitiveAndNotDefault()){
		format = true;
		newProfile.setAudioFormat(audioFormat.getActiveItem());
	}
	bool encoder = false;
	if(format && audioEncoder.isSensitiveAndNotDefault()){
		encoder = true;
		newProfile.setAudioEncoder(audioEncoder.getActiveItem());
	}
	if(encoder && audioGradeChooser.isSensitiveAndNotDefault()){
		newProfile.setAudioGrade(audioGradeChooser.getActiveItem());
	}
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
void EncoderControlA::setFormatsFromContainer(const MediaElement::Container& container){
	bool isSet = audioFormat.isNotDefaultLine();
	std::string actualFormat = "-";
	if(isSet){
		actualFormat = audioFormat.getActiveText();
	}

	audioFormat.remove_all();
	audioFormat.set_sensitive(true);

	auto names = elementsDB.elementsRelations.getFormatsByContainer(container);
	MediaElement::Formats formats = elementsDB.getFormats();
	for(auto name : names){
		MediaElement::Format format;
		if(formats.getFormatByName(name, MediaElement::Format::FORMAT_TYPE_AUDIO, format)){
			audioFormat.append(format.getName(), format);
		}
	}
	if(audioFormat.number_of_rows() == 0){
		this->disableSettings();
		return;
	}
	if(isSet){
		audioFormat.setActiveText(actualFormat);
	}
	if(audioFormat.getActiveText() != actualFormat){
		audioFormat.setActiveRowNumber(0);
	}
}
void EncoderControlA::aktualizeEncoder(){
	if(!audioFormat.isSensitiveAndNotDefault()){
		audioEncoder.set_sensitive(false);
		return;
	}
	bool isSet = audioEncoder.isNotDefaultLine();
	std::string actualEncoder = "-";
	if(isSet){
		actualEncoder = audioEncoder.getActiveText();
	}
	audioEncoder.set_sensitive(true);
	audioEncoder.remove_all();
	auto actualFormat = audioFormat.getActiveItem();

	auto names =  elementsDB.elementsRelations.getAudioEncodersByFormat(actualFormat);
	MediaElement::Encoders encoders = elementsDB.getAudioEncoders();
	for(auto name : names){
		MediaElement::Encoder encoder;
		if(encoders.getEncoderByName(name, encoder)){
			audioEncoder.append(encoder.getName(), encoder);
		}
	}
	if(isSet){
		audioEncoder.setActiveText(actualEncoder);
	}
	if(audioEncoder.getActiveText() != actualEncoder && audioEncoder.number_of_rows() > 0){
		audioEncoder.setActiveRowNumber(0);
	}
	if(audioEncoder.number_of_rows() == 0){
		audioEncoder.appendAndSet(NO_SUPPORTED_ENCODERS);
		audioEncoder.set_sensitive(false);
	}
}
void EncoderControlA::aktualizeBitrate(){
	if(!audioEncoder.isSensitiveAndNotDefault()){
		audioGradeChooser.set_sensitive(false);
		return;
	}
	bool isSetBitrate = audioGradeChooser.isNotDefaultLine();
	std::string actualBitrate = "";
	if(isSetBitrate){
		actualBitrate = audioGradeChooser.getActiveText();
	}
	audioGradeChooser.set_sensitive(true);
	audioGradeChooser.remove_all();
	auto actualEncoder = audioEncoder.getActiveItem();
	std::string bitratesName = elementsDB.elementsRelations.getAudioGradesByEncoder(actualEncoder);
	MediaElement::AudioGrades audioGrades;
	if(elementsDB.getAudioGradesByName(bitratesName, audioGrades)){
		for(auto grade : audioGrades){
			audioGradeChooser.append(grade.readableForm(), grade);
		}
	}
	if(isSetBitrate){
		audioGradeChooser.setActiveText(actualBitrate);
	}else{
		audioGradeChooser.setActiveRowNumber(audioGradeChooser.number_of_rows() / 2);
	}
}
void EncoderControlA::sendUserInputSignal(){
	if(isUserInput){
		userEvent();
	}
}
}
} /* namespace Gui */
