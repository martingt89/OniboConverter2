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
#include "XML/containersparser.h"
#include "XML/guisettingsparser.h"
#include "XML/encodersparser.h"
#include "FFTools/ffdatamining.h"
#include "datakeeper.h"

#include <glibmm/miscutils.h>
//#include "FFTools/ffpresets.h"	//todo add to datakeeper

void initSettings(){
	Settings *set = Settings::getSettings();
	set->setValue(Settings::FFPATH, "ffmpeg");
	set->setValue(Settings::ENCODERS, "encoders_table.xml");
	set->setValue(Settings::CONTAINERS, "container_settings.xml");
	set->setValue(Settings::GUISETTINGS, "gui_settings.xml");
	set->setValue(Settings::FFPRESENTSFOLDER, "ffpresets/");
	set->setValue(Settings::OUTPUTFOLDER, Glib::get_home_dir ());	//NEXT - rewrite to save settings
}

DataKeeper initData() {
	AVBox::AVBox audioVideoData;
	XML::ContainersParser parser;
	parser.parse(&audioVideoData);

	AVBox::GuiSettings guiData;
	XML::GuiSettingsParser guiParser;
	guiParser.parse(&guiData);

	AVBox::FormatToEncoders convert;
	XML::EncodersParser encodersParser;
	encodersParser.parse(&convert);

	AVBox::SupportedEncoders suportedEncoders;
	FFTools::FFDataMining dataMining;
	dataMining.scan(&suportedEncoders);

	DataKeeper keeper(audioVideoData, guiData, convert, suportedEncoders);
	return keeper;
}

int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);
	initSettings();

	DataKeeper keeper = initData();

	GUI::OniboWindow *window = 0;
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("graphic/model1.glade");
	builder->get_widget_derived("onibo_converter_window", window);
	window->setData(keeper);

	Gtk::Main::run(*window);

	delete window;

	return 0;
}
