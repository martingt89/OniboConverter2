/*
 * settingspart.h
 *
 *  Created on: 13.7.2012
 *      Author: martint
 */

#ifndef SETTINGSPART_H_
#define SETTINGSPART_H_

#include <gtkmm/notebook.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/comboboxtext.h>

#include "containercombobox.h"
#include "../datakeeper.h"
#include "../Tools/simplememorymanager.h"

namespace GUI {

class SettingsPart : public Gtk::Notebook{
public:
	SettingsPart(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	void setData(DataKeeper& keeper);
private:
	void showVideo();
	void showAudio();
	SimpleMemoryManager<Gtk::Widget> memoryManager;
	ContainerComboBox *container;
	Gtk::Button *videoSettings;
	Gtk::Button *audioSettings;
	Gtk::Button *outputFolder;
	Gtk::Entry *outputPath;
	Gtk::ComboBoxText *profilSelector;
};

} /* namespace GUI */
#endif /* SETTINGSPART_H_ */
