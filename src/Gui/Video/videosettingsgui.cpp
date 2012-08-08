/*
 * videosettingsgui.cpp
 *
 *  Created on: 8.8.2012
 *      Author: martint
 */

#include "videosettingsgui.h"
#include "../../helper.h"
namespace Gui {
static const std::string ORIGINAL = "original";

static const std::string COPY_MODE = "copy";
static const int COPY_MODE_ID = 0;
static const std::string CUSTOM_MODE = "custom";
static const int CUSTOM_MODE_ID = 1;
static const std::string DISABLE_MODE = "disable";
static const int DISABLE_MODE_ID = 2;

VideoSettingsGui::VideoSettingsGui(ConverterOptions::OptionsDatabase &database,
		const Glib::RefPtr<Gtk::Builder>& refGlade) : database(database), encoder(database, refGlade),
				videoMode(refGlade, "videoMode"), videoFramerate(refGlade,"videoFramerate"),
				videoResolution(refGlade,"videoResolution"){

	initVideoMode(videoMode);
	initVideoFramerate(videoFramerate);
	initVideoResolution(videoResolution);

	videoMode.signal_changed().connect(sigc::mem_fun(*this, &VideoSettingsGui::videoModeChanged));
	videoFramerate.signal_changed().connect(sigc::mem_fun(*this, &VideoSettingsGui::videoFramerateChanged));
	videoResolution.signal_changed().connect(sigc::mem_fun(*this, &VideoSettingsGui::videoResolutinChanged));
}

VideoSettingsGui::~VideoSettingsGui() {}

void VideoSettingsGui::disableSettings(){
	videoMode.set_sensitive(false);
	videoFramerate.set_sensitive(false);
	videoResolution.set_sensitive(false);
	encoder.disableSettings();
}

void VideoSettingsGui::videoContainerChanged(const ConverterOptions::Container& container){
	videoMode.set_sensitive(true);
	actualContainer = container;
	if(container.getContainerType() == ConverterOptions::Container::CONTAINER_TYPE_AUDIO){
		disableSettings();
		return;
	}
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

void VideoSettingsGui::saveSettingsState(){
	videoMode.save_actual_state();
	videoFramerate.save_actual_state();
	videoResolution.save_actual_state();
	encoder.saveSettingsState();
}
void VideoSettingsGui::restoreSettingsState(){
	videoResolution.restor_saved_state();
	videoFramerate.restor_saved_state();
	videoMode.restor_saved_state();
	encoder.restoreSettingsState();
}
bool VideoSettingsGui::checkSettingsComplete(std::string& message){
	videoResolution.isSet();
	videoFramerate.isSet();
	videoMode.isSet();
	return true;
}
void VideoSettingsGui::videoModeChanged(){
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
}
void VideoSettingsGui::videoFramerateChanged(){

}
void VideoSettingsGui::videoResolutinChanged(){

}
void VideoSettingsGui::initVideoMode(ComboBoxExt<int> &videoMode){
	videoMode.append(COPY_MODE, COPY_MODE_ID);
	videoMode.append(CUSTOM_MODE, CUSTOM_MODE_ID);
	videoMode.append(DISABLE_MODE, DISABLE_MODE_ID);
	videoMode.set_active_text(CUSTOM_MODE);
}
void VideoSettingsGui::initVideoFramerate(ComboBoxExt<ConverterOptions::Framerate> &videoFramerate){
	const std::list<ConverterOptions::Framerate> framerates = database.getFramerates().getFramerats();
	videoFramerate.append(ORIGINAL);
	videoFramerate.set_active_row_number(0);

	for(auto framerateIter = framerates.begin(); framerateIter != framerates.end(); ++framerateIter){
		videoFramerate.append(toS(framerateIter->getValue()), *framerateIter);
	}
}
void VideoSettingsGui::initVideoResolution(ComboBoxExt<ConverterOptions::Resolution> &videoResolution){
	const std::list<ConverterOptions::Resolution> resolutions = database.getResolutions().getResolutions();
	videoResolution.append(ORIGINAL);
	videoResolution.set_active_row_number(0);

	for(auto resolIter = resolutions.begin(); resolIter != resolutions.end(); ++resolIter){
		if(resolIter->isBasic()){
			std::string resolution = toS(resolIter->getValue().first)+" x "+toS(resolIter->getValue().second);
			resolution = resolution + "\t" + resolIter->getAspectRatio();
			videoResolution.append(resolution, *resolIter);
		}
	}
	videoResolution.append("--- more ---");
}

} /* namespace Gui */
