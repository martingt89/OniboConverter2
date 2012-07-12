/*
 * main.cpp
 *
 *  Created on: 20.6.2012
 *  Author: Martin Geier
 *
 *  Testing MediaInfo library
 */

#include <iostream>
#include "Tools/settings.h"
#include <gtkmm/main.h>
#include "Graphic/onibowindow.h"
#include "FFTools/ffpresets.h"

void initSettings(){
	Settings *set = Settings::getSettings();
	set->setValue(Settings::FFPATH, "ffmpeg");
	set->setValue(Settings::ENCODERS, "encoders_table.xml");
	set->setValue(Settings::CONTAINERS, "container_settings.xml");
	set->setValue(Settings::GUISETTINGS, "gui_settings.xml");
	set->setValue(Settings::FFPRESENTSFOLDER, "ffpresets/");
}
int main(int argc, char *argv[]){
	Gtk::Main kit(argc, argv);
	initSettings();

	GUI::OniboWindow *window = 0;
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("graphic/model1.glade");
	builder->get_widget_derived("onibo_converter_window", window);
	Gtk::Main::run(*window);

	return 0;
}
