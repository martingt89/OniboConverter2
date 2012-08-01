/*
 * guicontrols.h
 *
 *  Created on: 29.7.2012
 *      Author: martint
 */

#ifndef GUICONTROLS_H_
#define GUICONTROLS_H_

#include <list>
#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/builder.h>
#include "basiccontrols.h"
#include "../CppExtension/path.h"
#include "../ConverterOptions/optionsdatabase.h"
#include "../profil.h"
#include "settingsdialog.h"

namespace Gui {

class GuiControls {
public:
	GuiControls(ConverterOptions::OptionsDatabase &database, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~GuiControls();
	void setAvailableProfiles(const std::list<Profile>& availableProfiles);
	Gtk::Window& getProgramWindow();
private:
	ConverterOptions::OptionsDatabase &database;
	std::list<Profile> availableProfiles;
	//--------------------------------------------------
	void setCustomProfile();
	void setContainers(Gtk::ComboBoxText& containers, std::list<ConverterOptions::Container> items);
	void addCustomProfile(Gtk::ComboBoxText& profiles);
	void containerChanged();
	const Glib::RefPtr<Gtk::Builder>& refGlade;
	BasicControls* videoControls;
	BasicControls* audioControls;
	Gtk::Window *converterWindow;
	Gtk::Entry *outputPath;
	Gtk::Button *outputPathButton;
	Gtk::ComboBoxText *containers;
	Gtk::ComboBoxText *profiles;
	SettingsDialog* settingsDialog;
};

} /* namespace Gui */
#endif /* GUICONTROLS_H_ */
