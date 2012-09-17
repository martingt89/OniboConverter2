/* ---------------------------------------------------------------------------
** Author: Martin Geier
** usersettingsdialog.cpp is part of OniboConverter2.
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
