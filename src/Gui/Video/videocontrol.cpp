/*
 * videosettingsgui.cpp
 *
 *  Created on: 8.8.2012
 *      Author: martint
 */

#include "videocontrol.h"
#include "../../helper.h"

namespace Gui {
namespace Video {

static const std::string MORE_SETTINGS = "--- more ---";

static const std::string COPY_MODE = "copy";
static const int COPY_MODE_ID = 0;
static const std::string CUSTOM_MODE = "custom";
static const int CUSTOM_MODE_ID = 1;
static const std::string DISABLE_MODE = "disable";
static const int DISABLE_MODE_ID = 2;

VideoControl::VideoControl(MediaElement::ElementsDB& elementsDB,
		const Glib::RefPtr<Gtk::Builder>& refGlade) : elementsDB(elementsDB),
				encoder(elementsDB, refGlade),
				videoMode(refGlade, "videoMode"), videoFramerate(refGlade,"videoFramerate"),
				videoResolution(refGlade, "videoResolution"), resolutionDialog(elementsDB, refGlade) {

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
//Converter::ConvertSettingsList VideoControl::getConvertArguments() const{
//	Converter::ConvertSettingsList args;
//	if(videoMode.get_active_row_item() == CUSTOM_MODE_ID){
//		args.add(videoFramerate.get_active_row_item().getConvertArguments());
//		args.add(videoResolution.get_active_row_item().getConvertArguments());
//		args.add(encoder.getConvertArguments());
//	}else if(videoMode.get_active_row_item() == COPY_MODE_ID){
//		Converter::ConvertSettings arg(Converter::ConvertSettings::VCODEC);	//-vcodec
//		arg.addValue("copy");
//		args.add(arg);
//	}else if(videoMode.get_active_row_item() == DISABLE_MODE_ID){
//		Converter::ConvertSettings arg(Converter::ConvertSettings::NOVIDEO);	//-vn
//		args.add(arg);
//	}
//	return args;
//}
void VideoControl::setActiveProfile(const Profile::Profile& activeProfile){
	//set mode
	int row;
	if(activeProfile.getVideoMode(row)){
		videoMode.set_active_row_number(row);
		if(videoMode.get_active_row_item() == CUSTOM_MODE_ID){
			encoder.setActiveProfile(activeProfile);
		}else{
			disableSettings();
			videoMode.set_sensitive(true);
		}
	}else{
		videoMode.unset_active();
		disableSettings();
	}
	//set framerate
	MediaElement::Framerate framerate;
	if(activeProfile.getVideoFramerate(framerate)){
		videoFramerate.set_active_text(framerate.readableForm());
	}else{
		videoFramerate.unset_active();
	}
	//set resolution
	MediaElement::Resolution resolution;
	if(activeProfile.getVideoResolution(resolution)){
		if(!videoResolution.containes(resolution.readableForm())){
			videoResolution.insertBeforeLast(resolution.readableForm(), resolution);
		}
		videoResolution.set_active_text(resolution.readableForm());
	}else{
		videoFramerate.unset_active();
	}
}
void VideoControl::getNewProfile(Profile::Profile& newProfile){
	//video mode
	newProfile.setVideoMode(videoMode.get_active_row_number());

	if(videoMode.get_active_row_item() == CUSTOM_MODE_ID){
		encoder.getNewProfile(newProfile);
	}
	//video framerate
	if(videoFramerate.is_sensitive() && videoFramerate.is_selected()){
		newProfile.setVideoFramerate(videoFramerate.get_active_row_item());
	}
	//video resolution
	if(videoResolution.is_sensitive() && videoResolution.is_selected()){
		newProfile.setVideoResolution(videoResolution.get_active_row_item());
	}
}
void VideoControl::containerChanged(const MediaElement::Container& container){
	videoMode.set_sensitive(true);
	actualContainer = container;
	if(container.getContainerType() == MediaElement::Container::CONTAINER_TYPE_AUDIO){
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
	if(actualContainer.getContainerType() == MediaElement::Container::CONTAINER_TYPE_AUDIO_VIDEO){
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
			MediaElement::Resolution newResolution;
			if(resolutionDialog.start(newResolution)){
				std::string resolutionDescription = newResolution.readableForm();
				elementsDB.addUserResolution(newResolution);

				if(videoResolution.containes(resolutionDescription)){
					videoResolution.set_active_text(resolutionDescription);
				}else{
					videoResolution.insertBeforeLast(resolutionDescription, newResolution);
					videoResolution.set_active_text(resolutionDescription);
				}
			}else{
				if(lastSetResolution.isSet()){
					videoResolution.set_active_text(lastSetResolution.readableForm());
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
void VideoControl::initVideoFramerate(ComboBoxExt<MediaElement::Framerate> &videoFramerate){
	const std::list<MediaElement::Framerate> framerates = elementsDB.getFramerates().getFramerats();
	for(auto framerateIter = framerates.begin(); framerateIter != framerates.end(); ++framerateIter){
		videoFramerate.append(framerateIter->readableForm(), *framerateIter);
	}
	videoFramerate.set_active_row_number(0);
}
void VideoControl::initVideoResolution(ComboBoxExt<MediaElement::Resolution> &videoResolution){
	const std::list<MediaElement::Resolution> resolutions = elementsDB.getResolutions().getResolutions();
	for(auto resolIter = resolutions.begin(); resolIter != resolutions.end(); ++resolIter){
		if(resolIter->isBasic()){
			videoResolution.append(resolIter->readableForm(), *resolIter);
		}
	}
	videoResolution.set_active_row_number(0);
	videoResolution.append(MORE_SETTINGS);
}
void VideoControl::sendUserInputSignal(){
	userEvent();
}

}

} /* namespace Gui */
