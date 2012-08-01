/*
 * settingsdialog.cpp
 *
 *  Created on: 30.7.2012
 *      Author: martint
 */

#include "settingsdialog.h"

namespace Gui {

const static int VIDEO_SETTINGS = 0;
const static int AUDIO_SETTINGS = 1;
const static int RESOLUTION_SETTINGS = 2;
const static int ENCODER_SETTINGS = 3;

SettingsDialog::SettingsDialog(const Glib::RefPtr<Gtk::Builder>& refGlade) {
	closeCommand = false;
	refGlade->get_widget("settingsDialog", settingsDialog);
	refGlade->get_widget("settingsPages", settingsPages);
	settingsDialog->signal_hide().connect(sigc::mem_fun(*this, &SettingsDialog::signalHide));
}

SettingsDialog::~SettingsDialog() {
	delete settingsDialog;
}

void SettingsDialog::showVideoSettings(){
	settingsPages->set_current_page(VIDEO_SETTINGS);
	settingsDialog->show_all();
}
void SettingsDialog::showAudioSettings(){
	settingsPages->set_current_page(AUDIO_SETTINGS);
	settingsDialog->show_all();
}
void SettingsDialog::showResolutionSettings(){
	settingsPages->set_current_page(RESOLUTION_SETTINGS);
	settingsDialog->show_all();
}
void SettingsDialog::showEncoderSettings(){
	settingsPages->set_current_page(ENCODER_SETTINGS);
	settingsDialog->show_all();
}
void SettingsDialog::signalHide(){
	if(!closeCommand){
		closeWindow();
	}
}
void SettingsDialog::close(){
	closeCommand = true;
	settingsDialog->hide();
	closeCommand = false;
}
sigc::signal<void>& SettingsDialog::signalClose(){
	return closeWindow;
}

} /* namespace Gui */
