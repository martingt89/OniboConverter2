/*
 * main.cpp
 *
 *  Created on: 20.6.2012
 *  Author: Martin Geier
 *
 *  Testing MediaInfo library
 */

#include <iostream>
#include <gtkmm/main.h>
#include "Tools/settings.h"
#include "Graphic/onibowindow.h"
#include <glibmm/miscutils.h>
#include "AVBox/avbox.h"

void initSettings(){
	Settings *set = Settings::getSettings();
	set->setValue(Settings::FFPATH, "ffmpeg");
	set->setValue(Settings::ENCODERS, "encoders_table.xml");
	set->setValue(Settings::CONTAINERS, "container_settings.xml");
	set->setValue(Settings::GUISETTINGS, "gui_settings.xml");
	set->setValue(Settings::FFPRESENTSFOLDER, "ffpresets/");
	set->setValue(Settings::OUTPUTFOLDER, Glib::get_home_dir ());	//NEXT - rewrite to save settings
}

int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);
	initSettings();

	AVBox::AVBox availableAVSettings;

	GUI::OniboWindow *window = 0;
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("graphic/model1.glade");
	builder->get_widget_derived("onibo_converter_window", window);

	Gtk::Main::run(*window);

	delete window;

	return 0;
}
