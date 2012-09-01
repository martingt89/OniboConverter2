/*
 * videocontrolv.cpp
 *
 *  Created on: 8.8.2012
 *      Author: martint
 */

#include <gtkmm/stock.h>
#include "encodercontrolv.h"
#include "../../helper.h"

namespace Gui {
namespace Video {
static const std::string EXTEND_SETTING = "--- more ---";

EncoderControl::EncoderControl(ConverterOptions::OptionsDatabase &database,
		const Glib::RefPtr<Gtk::Builder>& refGlade) : database(database),
				videoFormat(refGlade, "videoFormat"), videoEncoder(refGlade, "videoEncoder"),
				videoBitrate(refGlade, "videoBitrate"), videoFFpreset(refGlade, "videoFFpreset"),
				ffpresetChooser("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN),
				bitrateDialog(database, refGlade){

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
	if(!videoFormat.isSelectedActivableRow()){
		message = "Video format is not set";
		return false;
	}
	if(!videoEncoder.isSelectedActivableRow()){
		message = "Video encoder is not set";
		return false;
	}
	if(!videoBitrate.isSelectedActivableRow()){
		message = "Video bitrate is not set";
		return false;
	}
	if(videoFFpreset.is_sensitive() && !videoFFpreset.is_selected()){
		message = "FFpreset is not set";
		return false;
	}
	return true;
}
void EncoderControl::setActiveProfile(const Profile::Profile& activeProfile){
	std::string formatName;
	bool format = false;
	if(activeProfile.getVideoFormatName(formatName)){
		videoFormat.set_active_text(formatName);
		if(videoFormat.get_active_text() == formatName){
			format = true;
		}
	}else{
		videoFormat.unset_active();
	}
	bool encoder = false;
	std::string encoderName;
	if(format && activeProfile.getVideoEncoderName(encoderName)){
		videoEncoder.set_active_text(encoderName);
		if(videoEncoder.get_active_text() == encoderName){
			encoder = true;
		}
	}else{
		videoEncoder.unset_active();
	}
	ConverterOptions::Bitrate bitrate;
	if(encoder && activeProfile.getVideoBitrate(bitrate)){
		if(!videoBitrate.containes(bitrate.toStr())){
			videoBitrate.insertBeforeLast(bitrate.toStr(), bitrate);
			database.addUserVideoBitrate(bitrate);
		}
		videoBitrate.set_active_text(bitrate.toStr());
	}else{
		videoBitrate.unset_active();
	}
	if(encoder && videoEncoder.get_active_row_item().hasFFpreset()){
		ConverterOptions::FFpreset ffpreset;
		if(activeProfile.getVideoFFpreset(ffpreset)){
			if(!videoFFpreset.containes(ffpreset.toStr()) && !ffpreset.isBuildIn()){
				videoFFpreset.insertBeforeLast(ffpreset.toStr(), ffpreset);
				database.addUserVideoFFpreset(ffpreset);
			}
			videoFFpreset.set_active_text(ffpreset.toStr());
		}else{
			videoFFpreset.unset_active();
		}
	}else{
		videoFFpreset.set_sensitive(false);
	}
}
Converter::ConvertSettingsList EncoderControl::getConvertArguments() const{
	Converter::ConvertSettingsList args;
	args.add(videoEncoder.get_active_row_item().getConvertArguments());
	args.add(videoBitrate.get_active_row_item().getConvertArguments());
	if(videoFFpreset.is_selected() && videoFFpreset.is_sensitive()){
		args.add(videoFFpreset.get_active_row_item().getConvertArguments());
	}
	return args;
}
void EncoderControl::getNewProfile(Profile::Profile& newProfile){
	bool format = false;
	if(videoFormat.is_sensitive() && videoFormat.is_selected()){
		format = true;
		newProfile.addProperty(Profile::Profile::VIDEO_FORMAT_OPT,
				videoFormat.get_active_row_item().getName());
	}
	bool encoder = false;
	if(format && videoEncoder.is_sensitive() && videoEncoder.is_selected()){
		encoder = true;
		newProfile.addProperty(Profile::Profile::VIDEO_ENCODER_OPT,
				videoEncoder.get_active_row_item().getName());
	}
	if(encoder && videoBitrate.isSelectedActivableRow()){
		newProfile.addProperty(Profile::Profile::VIDEO_BITRATE_OPT,
				toS(videoBitrate.get_active_row_item().getValue()));
		newProfile.addProperty(Profile::Profile::VIDEO_BITRATE_MAX_OPT,
				toS(videoBitrate.get_active_row_item().getMaxBitrate()));
		newProfile.addProperty(Profile::Profile::VIDEO_BITRATE_MIN_OPT,
				toS(videoBitrate.get_active_row_item().getMinBitrate()));
	}
	if(encoder && videoFFpreset.isSelectedActivableRow()){
		if(videoFFpreset.get_active_row_item().isBuildIn()){	//buildin
			newProfile.addProperty(Profile::Profile::VIDEO_FFPRESET_PATH_OPT,
					toS(videoFFpreset.get_active_row_item().getName()));
			newProfile.addProperty(Profile::Profile::VIDEO_FFPRESET_BUILDIN_OPT, "y");
		}else{
			newProfile.addProperty(Profile::Profile::VIDEO_FFPRESET_PATH_OPT,
					videoFFpreset.get_active_row_item().getPath().getPath());
		}
		newProfile.addProperty(Profile::Profile::VIDEO_FFPRESET_PREFIX_OPT,
				toS(videoFFpreset.get_active_row_item().getPrefix()));
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
			ConverterOptions::Bitrate userBitrate = lastSetBitrate;
			ConverterOptions::Bitrate savedBitrate = lastSetBitrate;
			bool set = bitrateDialog.start(videoEncoder.get_active_row_item(), userBitrate);
			if(set){
				if(!videoBitrate.containes(userBitrate.toStr())){
					videoBitrate.insertBeforeLast(userBitrate.toStr(), userBitrate);
					database.addUserVideoBitrate(userBitrate);
				}
				videoBitrate.set_active_text(userBitrate.toStr());
				if(!(userBitrate == savedBitrate)){
					sendUserInputSignal();
				}
			}else{
				videoBitrate.set_active_text(lastSetBitrate.toStr());
			}
		}else{
			sendUserInputSignal();
		}
		isEnableSignals = true;
	}
	lastSetBitrate = videoBitrate.get_active_row_item();
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
				ConverterOptions::FFpreset ff(ffFile, videoEncoder.get_active_row_item().getFFPrefix(), false);
				database.addUserVideoFFpreset(ff);
				aktualizeFFpreset(ff.toStr());
			}else{
				videoFFpreset.unset_active();
			}
		}
		sendUserInputSignal();
		isEnableSignals = true;
	}
}

void EncoderControl::setFormatsFromContainer(const ConverterOptions::Container& container){
	bool isSet = videoFormat.is_selected();
	std::string actualFormat = "-";
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
	if(videoFormat.get_active_text() != actualFormat){
		videoFormat.set_active_row_number(0);
	}
}
void EncoderControl::aktualizeEncoder(){
	if(!videoFormat.isSelectedActivableRow()){
		videoEncoder.set_sensitive(false);
		return;
	}
	bool isSet = videoEncoder.is_selected();
	std::string actualEncoder = "-";
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
	if(videoEncoder.get_active_text() != actualEncoder && encodersList.size() > 0){
		videoEncoder.set_active_row_number(0);
	}
	if(encodersList.size() == 0){
		videoEncoder.set_sensitive(false);	//todo text "no supported encoder"
	}
}

void EncoderControl::aktualizeBitrate(){
	if(!videoEncoder.isSelectedActivableRow()){
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
	auto userBitrateList = database.getUserVideoBitrate();
	std::copy(userBitrateList.begin(), userBitrateList.end(), std::back_inserter(bitratesList));
	std::for_each(bitratesList.begin(), bitratesList.end(), [&](const ConverterOptions::Bitrate& bitrate){
		videoBitrate.append(bitrate.toStr(), bitrate);
	});
	videoBitrate.append(EXTEND_SETTING);
	if(isSetBitrate){
		videoBitrate.set_active_text(actualBitrate);
	}else{
		videoBitrate.set_active_row_number(bitratesList.size() / 2);
	}
}

void EncoderControl::aktualizeFFpreset(const std::string name){
	if(!videoEncoder.isSelectedActivableRow() || !videoEncoder.get_active_row_item().hasFFpreset()){
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
	ConverterOptions::FFpresets ffpresets;
	videoEncoder.get_active_row_item().getFFPresets(ffpresets);
	std::list<ConverterOptions::FFpreset> ffpreset = ffpresets.getFFpresetList();
	for(auto ff : ffpreset){
		videoFFpreset.append(ff.toStr(), ff);
	}

	ffpreset = database.getUserFFpreset(videoEncoder.get_active_row_item().getFFPrefix());
	for(auto ff : ffpreset){
		videoFFpreset.append(ff.toStr(), ff);
	}

	if(name.size() > 0){
		videoFFpreset.set_active_text(name);
	}else if(isSetFFpreset){
		videoFFpreset.set_active_text(actualFFpreset);
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
