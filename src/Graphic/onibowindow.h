/*
 * onibowindow.h
 *
 *  Created on: 5.7.2012
 *      Author: martint
 */

#ifndef ONIBOWINDOW_H_
#define ONIBOWINDOW_H_

#include <gtkmm/window.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>

#include "settingspart.h"
#include "../AVBox/avbox.h"
#include "../AVBox/supportedencoders.h"
#include "../AVBox/formattoencoders.h"
#include "../AVBox/guisettings.h"
#include "../datakeeper.h"
#include "../Tools/simplememorymanager.h"

namespace GUI {

class OniboWindow : public Gtk::Window{
public:
	OniboWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	void setData(DataKeeper& keeper);
private:
	const Glib::RefPtr<Gtk::Builder>& refGlade;
	SettingsPart *settings;
	SimpleMemoryManager<Gtk::Widget> memoryManager;

	Gtk::Button *startConvert;
	Gtk::Button *addFile;
	Gtk::Button *removeFile;
	Gtk::Button *clear;

	AVBox::SupportedEncoders suportedEncoders;
	AVBox::AVBox audioVideoData;
	AVBox::GuiSettings guiData;
	AVBox::FormatToEncoders convert;
};

} /* namespace GUI */
#endif /* ONIBOWINDOW_H_ */
