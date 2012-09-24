/* ---------------------------------------------------------------------------
** Author: Martin Geier
** videocontrol.cpp is part of OniboConverter2.
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
void VideoControl::setActiveProfile(const Profile::Profile& activeProfile){
	//set mode
	int row;
	if(activeProfile.getVideoMode(row)){
		videoMode.setActiveRowNumber(row);
		if(videoMode.getActiveItem() == CUSTOM_MODE_ID){
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
		videoFramerate.setActiveText(framerate.readableForm());
	}else{
		videoFramerate.unset_active();
	}
	//set resolution
	MediaElement::Resolution resolution;
	if(activeProfile.getVideoResolution(resolution)){
		if(!videoResolution.containes(resolution.readableForm())){
			videoResolution.insertBeforeLast(resolution.readableForm(), resolution);
		}
		videoResolution.setActiveText(resolution.readableForm());
	}else{
		videoFramerate.unset_active();
	}
}
void VideoControl::getNewProfile(Profile::Profile& newProfile){
	//video mode
	newProfile.setVideoMode(videoMode.getActiveRowNumber());

	if(videoMode.getActiveItem() == CUSTOM_MODE_ID){
		encoder.getNewProfile(newProfile);
	}
	//video framerate
	if(videoFramerate.isSensitiveAndNotDefault()){
		newProfile.setVideoFramerate(videoFramerate.getActiveItem());
	}
	//video resolution
	if(videoResolution.isSensitiveAndNotDefault()){
		newProfile.setVideoResolution(videoResolution.getActiveItem());
	}
}
void VideoControl::containerChanged(const MediaElement::Container& container){
	videoMode.set_sensitive(true);
	actualContainer = container;
	if(container.getContainerType() == MediaElement::Container::CONTAINER_TYPE_AUDIO){
		disableSettings();
	}else{
		bool isSelected = videoMode.isNotDefaultLine();
		bool isEnableVideo = isSelected && (videoMode.getActiveItem() == CUSTOM_MODE_ID);
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
		if(!videoMode.isSensitiveAndNotDefault()){
			message = "Video mode is not set";
			return false;
		}
		if(videoMode.getActiveItem() == CUSTOM_MODE_ID){
			if(!videoResolution.isSensitiveAndNotDefault()){
				message = "Resolution is not set";
				return false;
			}
			if(!videoFramerate.isSensitiveAndNotDefault()){
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
		bool isSelected = videoMode.isNotDefaultLine();
		bool isEnableVideo = isSelected && (videoMode.getActiveItem() == CUSTOM_MODE_ID);
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
					videoResolution.setActiveText(resolutionDescription);
				}else{
					videoResolution.insertBeforeLast(resolutionDescription, newResolution);
					videoResolution.setActiveText(resolutionDescription);
				}
			}else{
				if(lastSetResolution.isSet()){
					videoResolution.setActiveText(lastSetResolution.readableForm());
				}else{
					videoResolution.setActiveRowNumber(0);
				}
			}
		}
		sendUserInputSignal();
	}
	lastSetResolution = videoResolution.getActiveItem();
}
void VideoControl::initVideoMode(ComboBoxExt<int> &videoMode){
	videoMode.append(COPY_MODE, COPY_MODE_ID);
	videoMode.append(CUSTOM_MODE, CUSTOM_MODE_ID);
	videoMode.append(DISABLE_MODE, DISABLE_MODE_ID);
	videoMode.setActiveText(CUSTOM_MODE);
}
void VideoControl::initVideoFramerate(ComboBoxExt<MediaElement::Framerate> &videoFramerate){
	const std::list<MediaElement::Framerate> framerates = elementsDB.getFramerates().getFramerats();
	for(auto framerateIter = framerates.begin(); framerateIter != framerates.end(); ++framerateIter){
		videoFramerate.append(framerateIter->readableForm(), *framerateIter);
	}
	videoFramerate.setActiveRowNumber(0);
}
void VideoControl::initVideoResolution(ComboBoxExt<MediaElement::Resolution> &videoResolution){
	const std::list<MediaElement::Resolution> resolutions = elementsDB.getResolutions().getResolutions();
	for(auto resolIter = resolutions.begin(); resolIter != resolutions.end(); ++resolIter){
		if(resolIter->isBasic()){
			videoResolution.append(resolIter->readableForm(), *resolIter);
		}
	}
	videoResolution.setActiveRowNumber(0);
	videoResolution.append(MORE_SETTINGS);
}
void VideoControl::sendUserInputSignal(){
	userEvent();
}

}

} /* namespace Gui */
