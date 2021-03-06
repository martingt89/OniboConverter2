/* ---------------------------------------------------------------------------
** Author: Martin Geier
** encodercontrolv.cpp is part of OniboConverter2.
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

#include <gtkmm/stock.h>
#include "encodercontrolv.h"
#include "../../helper.h"

namespace Gui {
namespace Video {
static const std::string EXTEND_SETTING = "--- more ---";
static const std::string NO_SUPPORTED_ENCODERS = "no supported encoders";

EncoderControl::EncoderControl(MediaElement::ElementsDB& elementsDB,
		const Glib::RefPtr<Gtk::Builder>& refGlade) : elementsDB(elementsDB),
				videoFormat(refGlade, "videoFormat"), videoEncoder(refGlade, "videoEncoder"),
				videoBitrate(refGlade, "videoBitrate"), videoFFpreset(refGlade, "videoFFpreset"),
				ffpresetChooser("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN),
				bitrateDialog(elementsDB, refGlade){

	isEnableSignals = true;
	isUserInput = true;
	initFileChooserDialog(ffpresetChooser);

	videoFormat.signal_changed().connect(sigc::mem_fun(*this, &EncoderControl::videoFormatChanged));
	videoEncoder.signal_changed().connect(sigc::mem_fun(*this, &EncoderControl::videoEncoderChanged));
	videoBitrate.signal_changed().connect(sigc::mem_fun(*this, &EncoderControl::videoBitrateChanged));
	videoFFpreset.signal_changed().connect(sigc::mem_fun(*this, &EncoderControl::videoFFpresetChanged));
}

EncoderControl::~EncoderControl() {}

void EncoderControl::aktualizeSettings(const bool& isVideoActive,
		const MediaElement::Container& container){
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
void EncoderControl::disableSettings(){
	videoFormat.set_sensitive(false);
	videoEncoder.set_sensitive(false);
	videoBitrate.set_sensitive(false);
	videoFFpreset.set_sensitive(false);
}
void EncoderControl::videoFormatChanged(){
	if(isEnableSignals){
		isEnableSignals = false;
		aktualizeEncoder();
		aktualizeBitrate();
		aktualizeFFpreset();
		isEnableSignals = true;
		sendUserInputSignal();
	}
}
void EncoderControl::saveSettingsState(){
	videoFormat.save_actual_state();
	videoEncoder.save_actual_state();
	videoBitrate.save_actual_state();
	videoFFpreset.save_actual_state();
}
void EncoderControl::restoreSettingsState(){
	isEnableSignals = false;
	videoFormat.restor_saved_state();
	videoEncoder.restor_saved_state();
	videoBitrate.restor_saved_state();
	videoFFpreset.restor_saved_state();
	isEnableSignals = true;
}

sigc::signal<void>& EncoderControl::signalUserInput(){
	return userEvent;
}
bool EncoderControl::checkSettingsComplete(std::string& message){
	if(!videoFormat.isSensitiveAndNotDefault()){
		message = "Video format is not set";
		return false;
	}
	if(!videoEncoder.isSensitiveAndNotDefault()){
		message = "Video encoder is not set";
		return false;
	}
	if(!videoBitrate.isSensitiveAndNotDefault()){
		message = "Video bitrate is not set";
		return false;
	}
	if(videoFFpreset.isSensitive() && !videoFFpreset.isNotDefaultLine()){
		message = "FFpreset is not set";
		return false;
	}
	return true;
}
void EncoderControl::setActiveProfile(const Profile::Profile& activeProfile){
	MediaElement::Format format;
	bool isFormat = false;

	if(activeProfile.getVideoFormat(format)){
		if(videoFormat.setActiveItem(format)){
			isFormat = true;
		}
	}else{
		videoFormat.unset_active();
	}
	bool isEncoder = false;
	MediaElement::Encoder encoder;
	if(isFormat && activeProfile.getVideoEncoder(encoder)){
		if(videoEncoder.setActiveItem(encoder)){
			isEncoder = true;
		}
	}else{
		videoEncoder.unset_active();
	}
	MediaElement::Bitrate bitrate;
	if(isEncoder && activeProfile.getVideoBitrate(bitrate)){
		if(!videoBitrate.containes(bitrate.readableForm())){
			videoBitrate.insertBeforeLast(bitrate.readableForm(), bitrate);
			elementsDB.addUserVideoBitrate(bitrate);
		}
		videoBitrate.setActiveText(bitrate.readableForm());
	}else{
		videoBitrate.unset_active();
	}

	std::string prefix;
	if(isEncoder && elementsDB.elementsRelations.getFFprefixByEncoder(encoder, prefix)){
		MediaElement::FFpreset ffpreset;
		if(activeProfile.getVideoFFpreset(ffpreset)){
			if(!videoFFpreset.containes(ffpreset.readableForm()) && !ffpreset.getType()){
				videoFFpreset.insertBeforeLast(ffpreset.readableForm(), ffpreset);
				elementsDB.addUserFFpreset(prefix, ffpreset);
			}
			videoFFpreset.setActiveText(ffpreset.readableForm());
		}else{
			videoFFpreset.unset_active();
		}
	}else{
		videoFFpreset.set_sensitive(false);
	}
}
void EncoderControl::getNewProfile(Profile::Profile& newProfile){
	bool format = false;
	if(videoFormat.isSensitiveAndNotDefault()){
		format = true;
		newProfile.setVideoFormat(videoFormat.getActiveItem());
	}
	bool encoder = false;
	if(format && videoEncoder.isSensitiveAndNotDefault()){
		encoder = true;
		newProfile.setVideoEncoder(videoEncoder.getActiveItem());
	}
	if(encoder && videoBitrate.isSensitiveAndNotDefault()){
		newProfile.setVideoBitrate(videoBitrate.getActiveItem());
	}
	if(encoder && videoFFpreset.isSensitiveAndNotDefault()){
		newProfile.setVideoFFpreset(videoFFpreset.getActiveItem());
	}
}
void EncoderControl::videoEncoderChanged(){
	if(isEnableSignals){
		isEnableSignals = false;
		aktualizeBitrate();
		aktualizeFFpreset();
		isEnableSignals = true;
		sendUserInputSignal();
	}
}

void EncoderControl::videoBitrateChanged(){
	if(isEnableSignals){
		isEnableSignals = false;
		if(videoBitrate.is_set_last()){
			MediaElement::Bitrate userBitrate = lastSetBitrate;
			MediaElement::Bitrate savedBitrate = lastSetBitrate;
			bool set = bitrateDialog.start(videoEncoder.getActiveItem(), userBitrate);
			if(set){
				if(!videoBitrate.containes(userBitrate.readableForm())){
					videoBitrate.insertBeforeLast(userBitrate.readableForm(), userBitrate);
					elementsDB.addUserVideoBitrate(userBitrate);
				}
				videoBitrate.setActiveText(userBitrate.readableForm());
				if(!(userBitrate == savedBitrate)){
					sendUserInputSignal();
				}
			}else{
				videoBitrate.setActiveText(lastSetBitrate.readableForm());
			}
		}else{
			sendUserInputSignal();
		}
		isEnableSignals = true;
	}
	lastSetBitrate = videoBitrate.getActiveItem();
}

void EncoderControl::videoFFpresetChanged(){
	if(isEnableSignals){
		isEnableSignals = false;

		if(videoFFpreset.is_set_last()){
			int res = ffpresetChooser.run();
			ffpresetChooser.hide();
			if(res == Gtk::RESPONSE_OK){
				Glib::RefPtr< Gio::File > file = ffpresetChooser.get_file ();
				Path ffFile(file->get_path());

				std::string prefix;
				elementsDB.elementsRelations.getFFprefixByEncoder(videoEncoder.getActiveItem(), prefix);
				MediaElement::FFpreset ff(ffFile, prefix, MediaElement::FFpreset::USERDEFINED_FFTYPE);
				elementsDB.addUserFFpreset(prefix, ff);
				aktualizeFFpreset(ff.readableForm());
			}else{
				videoFFpreset.unset_active();
			}
		}

		sendUserInputSignal();
		isEnableSignals = true;
	}
}

void EncoderControl::setFormatsFromContainer(const MediaElement::Container& container){
	bool isSet = videoFormat.isNotDefaultLine();
	std::string actualFormat = "-";
	if(isSet){
		actualFormat = videoFormat.getActiveText();
	}

	videoFormat.remove_all();
	videoFormat.set_sensitive(true);

	std::list<std::string> formatsNames = elementsDB.elementsRelations.getFormatsByContainer(container);

	for(std::string name : formatsNames){
		MediaElement::Format format;
		if(elementsDB.getFormats().getFormatByName(name, MediaElement::Format::FORMAT_TYPE_VIDEO, format)){
			videoFormat.append(format.readableForm(), format);
		}
	}
	if(isSet){
		videoFormat.setActiveText(actualFormat);
	}
	if(videoFormat.getActiveText() != actualFormat){
		videoFormat.setActiveRowNumber(0);
	}
	if(videoFormat.number_of_rows() == 0){
		disableSettings();
	}
}
void EncoderControl::aktualizeEncoder(){
	if(!videoFormat.isSensitiveAndNotDefault()){
		videoEncoder.set_sensitive(false);
		return;
	}
	bool isSet = videoEncoder.isNotDefaultLine();
	std::string actualEncoder = "-";
	if(isSet){
		actualEncoder = videoEncoder.getActiveText();
	}
	videoEncoder.set_sensitive(true);
	videoEncoder.remove_all();

	auto actualFormat = videoFormat.getActiveItem();

	std::list<std::string> encodersNames = elementsDB.elementsRelations.getVideoEncodersByFormat(actualFormat);
	for(std::string name : encodersNames){
		MediaElement::Encoder encoder;
		if(elementsDB.getVideoEncoders().getEncoderByName(name, encoder)){
			videoEncoder.append(encoder.readableForm(), encoder);
		}
	}
	if(isSet){
		videoEncoder.setActiveText(actualEncoder);
	}
	if(videoEncoder.getActiveText() != actualEncoder && videoEncoder.number_of_rows() > 0){
		videoEncoder.setActiveRowNumber(0);
	}
	if(videoEncoder.number_of_rows() == 0){
		videoEncoder.appendAndSet(NO_SUPPORTED_ENCODERS);
		videoEncoder.set_sensitive(false);
	}
}

void EncoderControl::aktualizeBitrate(){
	if(!videoEncoder.isSensitiveAndNotDefault()){
		videoBitrate.set_sensitive(false);
		return;
	}
	bool isSetBitrate = videoBitrate.isNotDefaultLine();
	std::string actualBitrate = "";
	if(isSetBitrate){
		actualBitrate = videoBitrate.getActiveText();
	}
	videoBitrate.set_sensitive(true);
	videoBitrate.remove_all();
	auto actualEncoder = videoEncoder.getActiveItem();

	std::string bitrateName = elementsDB.elementsRelations.getBitratesByEncoder(actualEncoder);
	MediaElement::Bitrates bitrates;
	if(elementsDB.getBitratesByName(bitrateName, bitrates)){
		for(auto bitrate : bitrates){
			videoBitrate.append(bitrate.readableForm(), bitrate);
		}
	}
	videoBitrate.append(EXTEND_SETTING);
	if(isSetBitrate){
		videoBitrate.setActiveText(actualBitrate);
	}else{
		videoBitrate.setActiveRowNumber(videoBitrate.number_of_rows() / 2);
	}
}

void EncoderControl::aktualizeFFpreset(const std::string name){
	if(!videoEncoder.isSensitiveAndNotDefault()){
		videoFFpreset.set_sensitive(false);
		return;
	}
	std::string prefix;
	if(!elementsDB.elementsRelations.getFFprefixByEncoder(videoEncoder.getActiveItem(), prefix)){
		videoFFpreset.set_sensitive(false);
		return;
	}

	bool isSetFFpreset = videoFFpreset.isNotDefaultLine();
	std::string actualFFpreset = "";
	if(isSetFFpreset){
		actualFFpreset = videoFFpreset.getActiveText();
	}
	videoFFpreset.set_sensitive(true);
	videoFFpreset.remove_all();
	std::list<MediaElement::FFpreset> ffpreset;
	elementsDB.getFFpresetsByPrefix(prefix, ffpreset);
	for(auto ff : ffpreset){
		videoFFpreset.append(ff.readableForm(), ff);
	}

	if(name.size() > 0){
		videoFFpreset.setActiveText(name);
	}else if(isSetFFpreset){
		videoFFpreset.setActiveText(actualFFpreset);
	}else{
		videoFFpreset.setActiveRowNumber(0);
	}
	videoFFpreset.append(EXTEND_SETTING);
}

void EncoderControl::sendUserInputSignal(){
	if(isUserInput){
		userEvent();
	}
}

void EncoderControl::initFileChooserDialog(Gtk::FileChooserDialog &fileChooserDialog) {
	fileChooserDialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	fileChooserDialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
	Glib::RefPtr<Gtk::FileFilter> filterFFpresets = Gtk::FileFilter::create();
	filterFFpresets->set_name("ffpreset");
	filterFFpresets->add_pattern("*.ffpreset");
	fileChooserDialog.add_filter(filterFFpresets);
	Glib::RefPtr<Gtk::FileFilter> filterAny = Gtk::FileFilter::create();
	filterAny->set_name("Any files");
	filterAny->add_pattern("*");
	fileChooserDialog.add_filter(filterAny);
}

}
} /* namespace Gui */
