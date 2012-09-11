/*
 * encodercontrol.cpp
 *
 *  Created on: 11.8.2012
 *      Author: martint
 */

#include "encodercontrola.h"

namespace Gui {
namespace Audio {
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
	if(!audioFormat.isSelectedActivableRow()){
		message = "Audio format is not set";
		return false;
	}
	if(!audioEncoder.isSelectedActivableRow()){
		message = "Audio encoder is not set";
		return false;
	}
	if(!audioGradeChooser.isSelectedActivableRow()){
		message = "Audio grade is not set";
		return false;
	}
	return true;
}
void EncoderControlA::setActiveProfile(const Profile::Profile& activeProfile){
	MediaElement::Format format;
	if(activeProfile.getAudioFormat(format)){
		audioFormat.set_active_text(format.readableForm());
		MediaElement::Encoder encoder;
		if(activeProfile.getAudioEncoder(encoder)){
			audioEncoder.set_active_text(encoder.readableForm());
			MediaElement::AudioGrade audioGrade;
			if(activeProfile.getAudioGrade(audioGrade)){
				audioGradeChooser.set_active_text(audioGrade.readableForm());
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
	if(audioFormat.isSelectedActivableRow()){
		format = true;
		newProfile.setAudioFormat(audioFormat.get_active_row_item());
	}
	bool encoder = false;
	if(format && audioEncoder.isSelectedActivableRow()){
		encoder = true;
		newProfile.setAudioEncoder(audioEncoder.get_active_row_item());
	}
	if(encoder && audioGradeChooser.isSelectedActivableRow()){
		newProfile.setAudioGrade(audioGradeChooser.get_active_row_item());
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
	bool isSet = audioFormat.is_selected();
	std::string actualFormat = "-";
	if(isSet){
		actualFormat = audioFormat.get_active_text();
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
	if(audioFormat.count_of_rows() == 0){
		this->disableSettings();
		return;
	}
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

	auto names =  elementsDB.elementsRelations.getAudioEncodersByFormat(actualFormat);
	MediaElement::Encoders encoders = elementsDB.getAudioEncoders();
	for(auto name : names){
		MediaElement::Encoder encoder;
		if(encoders.getEncoderByName(name, encoder)){
			audioEncoder.append(encoder.getName(), encoder);
		}
	}
	if(isSet){
		audioEncoder.set_active_text(actualEncoder);
	}
	if(audioEncoder.get_active_text() != actualEncoder && audioEncoder.count_of_rows() > 0){
		audioEncoder.set_active_row_number(0);
	}
	if(audioEncoder.count_of_rows() == 0){
		audioEncoder.set_sensitive(false);	//todo text "no supported encoder"
	}
}
void EncoderControlA::aktualizeBitrate(){
	if(!audioEncoder.isSelectedActivableRow()){
		audioGradeChooser.set_sensitive(false);
		return;
	}
	bool isSetBitrate = audioGradeChooser.is_selected();
	std::string actualBitrate = "";
	if(isSetBitrate){
		actualBitrate = audioGradeChooser.get_active_text();
	}
	audioGradeChooser.set_sensitive(true);
	audioGradeChooser.remove_all();
	auto actualEncoder = audioEncoder.get_active_row_item();
	std::string bitratesName = elementsDB.elementsRelations.getAudioGradesByEncoder(actualEncoder);
	MediaElement::AudioGrades audioGrades;
	if(elementsDB.getAudioGradesByName(bitratesName, audioGrades)){
		for(auto grade : audioGrades){
			audioGradeChooser.append(grade.readableForm(), grade);
		}
	}
	if(isSetBitrate){
		audioGradeChooser.set_active_text(actualBitrate);
	}else{
		audioGradeChooser.set_active_row_number(audioGradeChooser.count_of_rows() / 2);
	}
}
void EncoderControlA::sendUserInputSignal(){
	if(isUserInput){
		userEvent();
	}
}
}
} /* namespace Gui */
