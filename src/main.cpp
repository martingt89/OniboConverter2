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

#include "Profile/profile.h"
#include "Profile/profileloader.h"

#include <iostream> //todo remove

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
	Path profilesFolder("data/profiles");

	ExternalTools::SupportedEncodersLoader encodersLoader;
	ConverterOptions::SupportedEncoders encoders;
														//todo test if ffmpeg exist
	//bool res =
	encodersLoader.scan(encoders, ffmpeg);	//todo error message

	//Conv erterOptions::FFpreset ffpreset(ffpresetPath);

	ConverterOptions::OptionsLoaderXml optionsLoaderFromXml(xmlFilePath, encoders, ffpresetPath);

	ConverterOptions::OptionsDatabase optionsDatabase(&optionsLoaderFromXml);

	Profile::Profiles profiles;

	Profile::ProfileLoader loader;
	loader.load(profilesFolder, profiles);

	std::cout<<profiles.size()<<std::endl;

	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("data/model5.glade");

	Gui::ConverterGui converter(optionsDatabase, builder, profiles);

	Gtk::Main::run(converter.getWindow());

	return 0;
}
