/*
 * usersettingsdialog.cpp
 *
 *  Created on: 5.9.2012
 *      Author: martin
 */

#include "usersettingsdialog.h"
#include <gtkmm/stock.h>
#include "general.h"
#include "threading.h"

namespace Gui {
namespace Settings {

UserSettingsDialog::UserSettingsDialog(const Glib::RefPtr<Gtk::Builder>& refGlade) {
	refGlade->get_widget("userSettingsDialog", userSettingsDialog);
	userSettingsDialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	userSettingsDialog->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

	subSettings.push_back(new General(refGlade));
	subSettings.push_back(new Threading(refGlade));
}

UserSettingsDialog::~UserSettingsDialog() {
	for(auto subSetting : subSettings){
		delete subSetting;
	}
}

void UserSettingsDialog::start(){
	initGraphicElements();
	int res = userSettingsDialog->run();
	userSettingsDialog->hide();
	if(res == Gtk::RESPONSE_OK){
		aktualizeGlobalSettings();
		UserPreferences::getInstance()->save();
	}
}

void UserSettingsDialog::aktualizeGlobalSettings(){
	UserPreferences* preferences = UserPreferences::getInstance();
	for(auto subSetting : subSettings){
		subSetting->aktualizeGlobalSettings(preferences);
	}
}

void UserSettingsDialog::initGraphicElements(){
	UserPreferences* preferences = UserPreferences::getInstance();
	for(auto subSetting : subSettings){
		subSetting->initGraphicElements(preferences);
	}
}

} /* namespace Settings */
} /* namespace Gui */
