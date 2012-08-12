/*
 * main.cpp
 *
 *  Created on: 18.7.2012
 *      Author: martint
 */

#include <gtkmm/main.h>
#include <gtkmm/builder.h>
#include "ConverterOptions/optionsloaderxml.h"
#include "ConverterOptions/optionsdatabase.h"
#include "ConverterOptions/ffpreset.h"
#include "ConverterOptions/supportedencoders.h"
#include "CppExtension/path.h"
#include "ExternalTools/supportedencodersloader.h"
#include "Gui/convertergui.h"

/*
#include <iostream>

template<class T>

std::ostream& operator<<(std::ostream &os, const std::list<T>& t){
	typename std::list<T>::const_iterator it;
	for(it = t.begin(); it != t.end(); ++it){
		os << it->getName() <<" ";
	}
	return os;
}
*/
int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);
	Path ffpresetPath("ffpresets");
	Path xmlFilePath("data/audio_video_settings.xml");
	Path ffmpeg("ffmpeg");

	ExternalTools::SupportedEncodersLoader encodersLoader;
	ConverterOptions::SupportedEncoders encoders;
	bool res = encodersLoader.scan(encoders, ffmpeg);

	ConverterOptions::FFpreset ffpreset(ffpresetPath);

	ConverterOptions::OptionsLoaderXml optionsLoaderFromXml(xmlFilePath, encoders, &ffpreset);

	ConverterOptions::OptionsDatabase optionsDatabase(&optionsLoaderFromXml);

	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("data/model5.glade");

	Gui::ConverterGui converter(optionsDatabase, builder);

	Gtk::Main::run(converter.getWindow());

	return 0;
}
