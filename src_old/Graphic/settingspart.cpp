/*
 * settingspart.cpp
 *
 *  Created on: 13.7.2012
 *      Author: martint
 */

#include "settingspart.h"
#include "../Tools/settings.h"

namespace GUI {

SettingsPart::SettingsPart(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
	: Gtk::Notebook(cobject){

	refGlade->get_widget_derived("container_combo_box", container);
	refGlade->get_widget("video_settings", videoSettings);
	refGlade->get_widget("audio_settings", audioSettings);
	refGlade->get_widget("output_path", outputPath);

	outputFolder = 0;
	profilSelector = 0;

	memoryManager.addObject(container);
	memoryManager.addObject(videoSettings);
	memoryManager.addObject(audioSettings);
	memoryManager.addObject(outputFolder);
	memoryManager.addObject(outputPath);
	memoryManager.addObject(profilSelector);

	outputPath->set_text(Settings::getSettings()->getValue(Settings::OUTPUTFOLDER));

	videoSettings->signal_clicked().connect(sigc::mem_fun(*this, &SettingsPart::showVideo));
	audioSettings->signal_clicked().connect(sigc::mem_fun(*this, &SettingsPart::showAudio));

	//container->userEvent.connect(sigc::mem_fun(*this, &SettingsPart::showAudio));
}
void SettingsPart::setData(DataKeeper& keeper){
	container->setData(keeper);
	//todo ulozit nieco co vie robit s profilmy
}

void SettingsPart::showVideo(){
	this->set_current_page(1);
}
void SettingsPart::showAudio(){
	this->set_current_page(2);
}
} /* namespace GUI */
