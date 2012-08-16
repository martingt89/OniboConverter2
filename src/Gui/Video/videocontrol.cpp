/*
 * videosettingsgui.cpp
 *
 *  Created on: 8.8.2012
 *      Author: martint
 */

#include "videocontrol.h"
#include "../../helper.h"
#include <iostream> //todo remove

namespace Gui {
namespace Video {

static const std::string ORIGINAL = "--- original ---";
static const std::string MORE_SETTINGS = "--- more ---";

static const std::string COPY_MODE = "copy";
static const int COPY_MODE_ID = 0;
static const std::string CUSTOM_MODE = "custom";
static const int CUSTOM_MODE_ID = 1;
static const std::string DISABLE_MODE = "disable";
static const int DISABLE_MODE_ID = 2;

VideoControl::VideoControl(ConverterOptions::OptionsDatabase &database,
		const Glib::RefPtr<Gtk::Builder>& refGlade) : database(database), encoder(database, refGlade),
				videoMode(refGlade, "videoMode"), videoFramerate(refGlade,"videoFramerate"),
				videoResolution(refGlade, "videoResolution"),resolutionDialog(database, refGlade) {

	isEnabledSignals = true;

	initVideoMode(videoMode);
	initVideoFramerate(videoFramerate);
	initVideoResolution(videoResolution);

	videoMode.signal_changed().connect(sigc::mem_fun(*this, &VideoControl::videoModeChanged));
	videoFramerate.signal_changed().connect(sigc::mem_fun(*this, &VideoControl::videoFramerateChanged));
	videoResolution.signal_changed().connect(sigc::mem_fun(*this, &VideoControl::videoResolutinChanged));
	encoder.signalUserInput().connect(sigc::mem_fun(*this, &VideoControl::encoderUserInput));
}

VideoControl::~VideoControl() {}

void VideoControl::disableSettings(){
	videoMode.set_sensitive(false);
	videoFramerate.set_sensitive(false);
	videoResolution.set_sensitive(false);
	encoder.disableSettings();
}
sigc::signal<void>& VideoControl::signalUserInput(){
	return userEvent;
}
void VideoControl::setActiveProfile(const Profile::Profile& activeProfile){
	//set mode
	int row;
	if(activeProfile.getVideoMode(row)){
		videoMode.set_active_row_number(row);
		if(videoMode.get_active_row_item() == CUSTOM_MODE_ID){
			encoder.setActiveProfile(activeProfile);
		}else{
			disableSettings();
		}
	}else{
		videoMode.unset_active();
		disableSettings();
	}
	//set framerate
	ConverterOptions::Framerate framerate;
	bool isOriginal;
	if(activeProfile.getVideoFramerate(framerate, isOriginal)){
		if(isOriginal){
			videoFramerate.set_active_row_number(0);
		}else{
			videoFramerate.set_active_text(toS(framerate.getValue()));
		}
	}else{
		videoFramerate.unset_active();
	}
	//set resolution
	ConverterOptions::Resolution resolution;
	if(activeProfile.getVideoResolution(resolution, isOriginal)){
		if(isOriginal){
			videoResolution.set_active_row_number(0);
		}else{
			if(!videoResolution.containes(resolution.toStr())){
				videoResolution.insertAfterLast(resolution.toStr(), resolution);
			}
			videoResolution.set_active_text(resolution.toStr());
		}
	}else{
		videoFramerate.unset_active();
	}
}
void VideoControl::containerChanged(const ConverterOptions::Container& container){
	videoMode.set_sensitive(true);
	actualContainer = container;
	if(container.getContainerType() == ConverterOptions::Container::CONTAINER_TYPE_AUDIO){
		disableSettings();
	}else{
		bool isSelected = videoMode.is_selected();
		bool isEnableVideo = isSelected && (videoMode.get_active_row_item() == CUSTOM_MODE_ID);
		encoder.aktualizeSettings(isEnableVideo, container);

		if(isEnableVideo){
			videoFramerate.set_sensitive(true);
			videoResolution.set_sensitive(true);
		}else{
			videoFramerate.set_sensitive(false);
			videoResolution.set_sensitive(false);
		}
	}
}

void VideoControl::saveSettingsState(){
	videoMode.save_actual_state();
	videoFramerate.save_actual_state();
	videoResolution.save_actual_state();
	encoder.saveSettingsState();
}
void VideoControl::restoreSettingsState(){
	isEnabledSignals = false;
	videoResolution.restor_saved_state();
	videoFramerate.restor_saved_state();
	videoMode.restor_saved_state();
	encoder.restoreSettingsState();
	isEnabledSignals = true;
}
bool VideoControl::checkSettingsComplete(std::string& message){
	if(!videoMode.isSelectedActivableRow()){
		message = "Video mode is not set";
		return false;
	}
	if(videoMode.get_active_row_item() == CUSTOM_MODE_ID){
		if(!videoResolution.isSelectedActivableRow()){
			message = "Resolution is not set";
			return false;
		}
		if(!videoFramerate.isSelectedActivableRow()){
			message = "Video framerate is not set";
			return false;
		}
		if(!encoder.checkSettingsComplete(message)){
			return false;
		}
	}
	return true;
}
void VideoControl::encoderUserInput(){
	sendUserInputSignal();
}
void VideoControl::videoModeChanged(){
	if(isEnabledSignals){
		isEnabledSignals = false;
		bool isSelected = videoMode.is_selected();
		bool isEnableVideo = isSelected && (videoMode.get_active_row_item() == CUSTOM_MODE_ID);
		encoder.aktualizeSettings(isEnableVideo, actualContainer);
		if(isEnableVideo){
			videoFramerate.set_sensitive(true);
			videoResolution.set_sensitive(true);
		}else{
			videoFramerate.set_sensitive(false);
			videoResolution.set_sensitive(false);
		}
		sendUserInputSignal();
		isEnabledSignals = true;
	}
}
void VideoControl::videoFramerateChanged(){
	if(isEnabledSignals){
		sendUserInputSignal();
	}
}
void VideoControl::videoResolutinChanged(){
	if(isEnabledSignals){
		if(videoResolution.is_set_last()){
			ConverterOptions::Resolution newResolution;
			if(resolutionDialog.start(newResolution)){
				std::string resolutionDescription = newResolution.toStr();
				database.addUserResolution(newResolution);
				if(videoResolution.containes(resolutionDescription)){
					videoResolution.set_active_text(resolutionDescription);
				}else{
					videoResolution.insertAfterLast(resolutionDescription, newResolution);
					videoResolution.set_active_text(resolutionDescription);
				}
			}else{
				if(lastSetResolution.isSet()){
					videoResolution.set_active_text(lastSetResolution.toStr());
				}else{
					videoResolution.set_active_row_number(0);
				}
			}
		}
		sendUserInputSignal();
	}
	lastSetResolution = videoResolution.get_active_row_item();
}
void VideoControl::initVideoMode(ComboBoxExt<int> &videoMode){
	videoMode.append(COPY_MODE, COPY_MODE_ID);
	videoMode.append(CUSTOM_MODE, CUSTOM_MODE_ID);
	videoMode.append(DISABLE_MODE, DISABLE_MODE_ID);
	videoMode.set_active_text(CUSTOM_MODE);
}
void VideoControl::initVideoFramerate(ComboBoxExt<ConverterOptions::Framerate> &videoFramerate){
	const std::list<ConverterOptions::Framerate> framerates = database.getFramerates().getFramerats();
	videoFramerate.append(ORIGINAL);
	videoFramerate.set_active_row_number(0);

	for(auto framerateIter = framerates.begin(); framerateIter != framerates.end(); ++framerateIter){
		videoFramerate.append(toS(framerateIter->getValue()), *framerateIter);
	}
}
void VideoControl::initVideoResolution(ComboBoxExt<ConverterOptions::Resolution> &videoResolution){
	const std::list<ConverterOptions::Resolution> resolutions = database.getResolutions().getResolutions();
	videoResolution.append(ORIGINAL);
	videoResolution.set_active_row_number(0);

	for(auto resolIter = resolutions.begin(); resolIter != resolutions.end(); ++resolIter){
		if(resolIter->isBasic()){
			videoResolution.append(resolIter->toStr(), *resolIter);
		}
	}
	videoResolution.append(MORE_SETTINGS);
}
void VideoControl::sendUserInputSignal(){
	userEvent();
}

}

} /* namespace Gui */
