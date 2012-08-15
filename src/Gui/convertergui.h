/*
 * convertergui.h
 *
 *  Created on: 7.8.2012
 *      Author: martint
 */

#ifndef CONVERTERGUI_H_
#define CONVERTERGUI_H_

#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/builder.h>
#include <gtkmm/notebook.h>
#include <gtkmm/messagedialog.h>
#include "../Profile/profile.h"
#include "../ConverterOptions/optionsdatabase.h"
#include "avcontrol.h"

namespace Gui {

class ConverterGui {
public:
	ConverterGui(ConverterOptions::OptionsDatabase &database,
			const Glib::RefPtr<Gtk::Builder>& refGlade,
			const Profile::Profiles& profiles);
	void setAvailableProfiles(const std::list<Profile::Profile>& availableProfiles);
	Gtk::Window& getWindow();
	virtual ~ConverterGui();
private:
	void settingsButtonClicked();
	void okSettingsButtonClicked();
	void cancelSettingsButtonClicked();

	ConverterOptions::OptionsDatabase &database;
	AVControl mainSettings;
	Gtk::Window* mainWindow;
	Gtk::Button* settingsButton;
	Gtk::Button* okSettingsButton;
	Gtk::Button* cancelSettingsButton;
	Gtk::Notebook* mainNotebook;
	Gtk::MessageDialog warningDialog;

	Gtk::Entry* entry;
};

} /* namespace Gui */
#endif /* CONVERTERGUI_H_ */
