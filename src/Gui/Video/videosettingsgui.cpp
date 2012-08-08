/*
 * videosettingsgui.cpp
 *
 *  Created on: 8.8.2012
 *      Author: martint
 */

#include "videosettingsgui.h"
#include "../../helper.h"
namespace Gui {

static const std::string COPY_MODE = "copy";
static const int COPY_MODE_ID = 0;
static const std::string CUSTOM_MODE = "custom";
static const int CUSTOM_MODE_ID = 1;
static const std::string DISABLE_MODE = "disable";
static const int DISABLE_MODE_ID = 2;

VideoSettingsGui::VideoSettingsGui(ConverterOptions::OptionsDatabase &database,
		const Glib::RefPtr<Gtk::Builder>& refGlade) : database(database) {

	Gtk::ComboBoxText* _videoMode;
	refGlade->get_widget("videoMode", _videoMode);
	videoMode.set_comboboxtext_widget(_videoMode);
	initVideoMode(videoMode);

	Gtk::ComboBoxText* _videoFramerate;
	refGlade->get_widget("videoFramerate", _videoFramerate);
	videoFramerate.set_comboboxtext_widget(_videoFramerate);
	initVideoFramerate(videoFramerate);

	Gtk::ComboBoxText* _videoResolution;
	refGlade->get_widget("videoResolution", _videoResolution);
	videoResolution.set_comboboxtext_widget(_videoResolution);
	initVideoResolution(videoResolution);
}

VideoSettingsGui::~VideoSettingsGui() {
	// TODO Auto-generated destructor stub
}
void VideoSettingsGui::saveSettingsState(){
	videoMode.save_actual_state();
	videoFramerate.save_actual_state();
	videoResolution.save_actual_state();
}
void VideoSettingsGui::restoreSettingsState(){
	videoResolution.restor_saved_state();
	videoFramerate.restor_saved_state();
	videoMode.restor_saved_state();
}
bool VideoSettingsGui::checkSettingsComplete(std::string& message){

	return true;
}

void VideoSettingsGui::initVideoMode(ComboBoxExt<int> &videoMode){
	videoMode.append(COPY_MODE, COPY_MODE_ID);
	videoMode.append(CUSTOM_MODE, CUSTOM_MODE_ID);
	videoMode.append(DISABLE_MODE, DISABLE_MODE_ID);
}
void VideoSettingsGui::initVideoFramerate(ComboBoxExt<ConverterOptions::Framerate> &videoFramerate){
	const std::list<ConverterOptions::Framerate> framerates = database.getFramerates().getFramerats();

	for(auto framerateIter = framerates.begin(); framerateIter != framerates.end(); ++framerateIter){
		videoFramerate.append(toS(framerateIter->getValue()), *framerateIter);
	}
}
void VideoSettingsGui::initVideoResolution(ComboBoxExt<ConverterOptions::Resolution> &videoResolution){
	const std::list<ConverterOptions::Resolution> resolutions = database.getResolutions().getResolutions();

	for(auto resolIter = resolutions.begin(); resolIter != resolutions.end(); ++resolIter){
		if(resolIter->isBasic()){
			std::string resolution = toS(resolIter->getValue().first)+" x "+toS(resolIter->getValue().second);
			resolution = resolution + "\t" + resolIter->getAspectRatio();
			videoResolution.append(resolution, *resolIter);
		}
	}
}

} /* namespace Gui */
