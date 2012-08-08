/*
 * videogui.cpp
 *
 *  Created on: 29.7.2012
 *      Author: martint
 */

#include "globalvideosettings.h"
#include "../../helper.h"
#include <iostream> //remove

namespace Gui {

const static std::string COPY_STRING="copy";
const static int COPY_ID=0;
const static std::string CUSTOM_STRING="custom";
const static int CUSTOM_ID=1;
const static std::string DISABLE_STRING="disable";
const static int DISABLE_ID=2;
const static std::string KEEP_ORIGINAL="original";

GlobalVideoSettings::GlobalVideoSettings(ConverterOptions::OptionsDatabase &database,
		const Glib::RefPtr<Gtk::Builder>& refGlade,
		SettingsDialog& settingsDialog): database(database),settingsDialog(settingsDialog)  {

	isLockSignal = false;
	activeContainerName = "";

	loadComboBoxes(refGlade);

	encoderSettings = new EncoderSettings(database, videoFormat, videoEncoder, videoBitrate, videoFFpreset);

	refGlade->get_widget("showVideoSettings",showVideoSettings);
	showVideoSettings->set_sensitive(false);
	refGlade->get_widget("okVideoButton",okVideoButton);
	refGlade->get_widget("cancelVideoButton",cancelVideoButton);
	refGlade->get_widget("videoErrorMessage",videoErrorMessage);

	initVideoMode(videoMode);
	initResolution(videoResolution, database);
	initFramerate(videoFramerate, database);

	showVideoSettings->signal_clicked()
			.connect(sigc::mem_fun(*this, &GlobalVideoSettings::showVideoSettingsClicked));
	okVideoButton->signal_clicked()
					.connect(sigc::mem_fun(*this, &GlobalVideoSettings::okButtonClicked));
	cancelVideoButton->signal_clicked()
					.connect(sigc::mem_fun(*this, &GlobalVideoSettings::cancelButtonClicked));
	settingsDialog.signalClose()
					.connect(sigc::mem_fun(*this, &GlobalVideoSettings::cancelButtonClicked));
	videoMode.signal_changed().connect(sigc::mem_fun(*this, &GlobalVideoSettings::videoModeChanged));
	videoFormat.signal_changed().connect(sigc::mem_fun(*this, &GlobalVideoSettings::videoFormatChanged));
	videoEncoder.signal_changed().connect(sigc::mem_fun(*this, &GlobalVideoSettings::videoEncoderChanged));
	videoBitrate.signal_changed().connect(sigc::mem_fun(*this, &GlobalVideoSettings::videoBitrateChanged));
}

GlobalVideoSettings::~GlobalVideoSettings() {
	delete showVideoSettings;
}

void GlobalVideoSettings::setActiveProfile(Profile activeProfile){

}

sigc::signal<void>& GlobalVideoSettings::signalUserInput(){
	return userInput;
}

void GlobalVideoSettings::setActiveContainer(ConverterOptions::Container container){
	activeContainerName = container.getName();
	showVideoSettings->set_sensitive(true);
	if(container.getContainerType() == ConverterOptions::Container::CONTAINER_TYPE_AUDIO){
		setUnsesitiveVideoDialog();
	}else{
		videoMode.set_sensitive(true);
		bool isEditableVideo = isVideoModeEditable();
		if(isEditableVideo){
			encoderSettings->fillVideoFormats(container.getFormats().getVideoFormatsList());
			videoFormat.set_sensitive(true);
			videoResolution.set_sensitive(true);
			videoFramerate.set_sensitive(true);
		}else{
			setUnsensitiveVideoSettings();
		}
	}
}
void GlobalVideoSettings::videoModeChanged(){
	if(isLockSignal) return;
	isLockSignal = true;
	bool isEditableVideo = isVideoModeEditable();
	if(isEditableVideo){
		ConverterOptions::Container container = getActiveContainer();
		encoderSettings->fillVideoFormats(container.getFormats().getVideoFormatsList());
		videoFormat.set_sensitive(true);
		videoResolution.set_sensitive(true);
		videoFramerate.set_sensitive(true);
	}else{
		setUnsensitiveVideoSettings();
	}
	isLockSignal = false;
	userInput();
}
//===========================================================================
void GlobalVideoSettings::videoFormatChanged(){
	if(isLockSignal) return;
	isLockSignal = true;
	encoderSettings->videoFormatChanged();
	isLockSignal = false;
	userInput();
}
void GlobalVideoSettings::videoEncoderChanged(){
	if(isLockSignal) return;
	isLockSignal = true;
	encoderSettings->videoEncoderChanged();
	isLockSignal = false;
	userInput();
}
void GlobalVideoSettings::videoBitrateChanged(){
	if(isLockSignal) return;
	userInput();
}
void GlobalVideoSettings::showVideoSettingsClicked(){
	videoErrorMessage->set_text("");
	saveActualSettings();
	settingsDialog.showVideoSettings();
}
void GlobalVideoSettings::cancelButtonClicked(){
	settingsDialog.close();
	restorActualSettings();
	std::cout<<"Cancel"<<std::endl;
}
void GlobalVideoSettings::okButtonClicked(){
	std::cout<<"OK"<<std::endl;
	std::string message = "";
	if(isVideoModeEditable() && !encoderSettings->isAllSet(message)){
		videoErrorMessage->set_markup("<span color='red'> "+message+" </span>");
	}else{
		settingsDialog.close();
	}
}
//==========================================================================
void GlobalVideoSettings::saveActualSettings(){
	videoMode.save_actual_state();
	videoFormat.save_actual_state();
	videoEncoder.save_actual_state();
	videoBitrate.save_actual_state();
	videoFFpreset.save_actual_state();
	videoFramerate.save_actual_state();
	videoResolution.save_actual_state();
}
void GlobalVideoSettings::restorActualSettings(){
	bool lock = isLockSignal;
	isLockSignal = true;
	videoMode.restor_saved_state();
	videoFormat.restor_saved_state();
	videoEncoder.restor_saved_state();
	videoBitrate.restor_saved_state();
	videoFFpreset.restor_saved_state();
	videoFramerate.restor_saved_state();
	videoResolution.restor_saved_state();
	isLockSignal = lock;
}
void GlobalVideoSettings::setUnsesitiveVideoDialog(){
	setUnsensitiveVideoSettings();
	videoMode.set_sensitive(false);
}
void GlobalVideoSettings::setUnsensitiveVideoSettings(){
	encoderSettings->setUnsensitive();
	videoFramerate.set_sensitive(false);
	videoResolution.set_sensitive(false);
}
bool GlobalVideoSettings::isVideoModeEditable(){
	bool isSeleced;
	bool isEd = videoMode.is_sensitive() && videoMode.get_active_row_item(isSeleced) == CUSTOM_ID;
	return isSeleced && isEd;
}
ConverterOptions::Container GlobalVideoSettings::getActiveContainer(){
	if(activeContainerName.size() == 0){
		std::cerr<<"Assert activeContainerName.size() != 0"<<std::endl;
		_exit(1);
	}
	return database.getContainers().getContainerByName(activeContainerName);
}
//==========================================================================
void GlobalVideoSettings::initVideoMode(ComboBoxExt<int>& videoMode){
	videoMode.append(COPY_STRING, COPY_ID);
	videoMode.append(CUSTOM_STRING, CUSTOM_ID);
	videoMode.append(DISABLE_STRING, DISABLE_ID);
	videoMode.set_active_row_number(CUSTOM_ID);
}
void GlobalVideoSettings::initResolution(ComboBoxExt<std::string>& videoResolution,
		ConverterOptions::OptionsDatabase &database){
	videoResolution.append(KEEP_ORIGINAL);
	videoResolution.set_active_row_number(0);
	std::list<ConverterOptions::Resolution> resol = database.getResolutions().getResolutions();
	for(auto resolIter = resol.begin(); resolIter != resol.end(); ++resolIter){
		if (resolIter->isBasic()){
			std::pair<int, int> resolution = resolIter->getValue();
			videoResolution.append(toS(resolution.first)+" x "+toS(resolution.second)
					+"\t"+resolIter->getAspectRatio(), resolIter->getName());
		}
	}
}
void GlobalVideoSettings::initFramerate(ComboBoxExt<int>& videoFramerate, ConverterOptions::OptionsDatabase &database){
	std::list<ConverterOptions::Framerate> framerates = database.getFramerates().getFramerats();
	videoFramerate.append(KEEP_ORIGINAL);
	videoFramerate.set_active_row_number(0);
	for (auto frameratesIter = framerates.begin(); frameratesIter != framerates.end(); ++frameratesIter){
		videoFramerate.append(toS(frameratesIter->getValue()));
	}
}
void GlobalVideoSettings::loadComboBoxes(const Glib::RefPtr<Gtk::Builder>& refGlade){
	Gtk::ComboBoxText* _videoMode;
	refGlade->get_widget("videoMode", _videoMode);
	videoMode.set_comboboxtext_widget(_videoMode);

	Gtk::ComboBoxText* _videoFormat;
	refGlade->get_widget("videoFormat", _videoFormat);
	videoFormat.set_comboboxtext_widget(_videoFormat);

	Gtk::ComboBoxText* _videoEncoder;
	refGlade->get_widget("videoEncoder", _videoEncoder);
	videoEncoder.set_comboboxtext_widget(_videoEncoder);

	Gtk::ComboBoxText* _videoFramerate;
	refGlade->get_widget("videoFramerate", _videoFramerate);
	videoFramerate.set_comboboxtext_widget(_videoFramerate);

	Gtk::ComboBoxText* _videoBitrate;
	refGlade->get_widget("videoBitrate", _videoBitrate);
	videoBitrate.set_comboboxtext_widget(_videoBitrate);

	Gtk::ComboBoxText* _videoResolution;
	refGlade->get_widget("videoResolution", _videoResolution);
	videoResolution.set_comboboxtext_widget(_videoResolution);

	Gtk::ComboBoxText* _videoFFpreset;
	refGlade->get_widget("videoFFpreset", _videoFFpreset);
	videoFFpreset.set_comboboxtext_widget(_videoFFpreset);
}
} /* namespace Gui */
