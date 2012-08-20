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
#include "MediaFile/mediafile.h"
#include "Profile/profile.h"
#include "Profile/profileloader.h"

#include <iostream>
class OniboConverter{
private:
	Path ffpresetPath;
	Path xmlFilePath;
	Path ffmpeg;
	Path profilesFolder;
	Gui::ConverterGui* converterGui;
public:
	OniboConverter(): ffpresetPath("ffpresets"),
	xmlFilePath("data/audio_video_settings.xml"), ffmpeg("ffmpeg"), profilesFolder("data/profiles"),
	converterGui(NULL){}

	void convert(std::list<MediaFile::MediaFile> mediaFiles){
		for(MediaFile::MediaFile file : mediaFiles){
			if(!file.isSet()){
				file.scanMediaFile();
			}
			if(file.isValid()){
				std::cout<<file.getDuration()<<std::endl;
				std::cout<<file.getBitrate()<<std::endl;
				std::cout<<file.getStartTime()<<std::endl;
				std::cout<<file.getNumberOfVideoStreams()<<std::endl;
			}
		}
	}

	void run(int argc, char *argv[]){
		Gtk::Main kit(argc, argv);
		ExternalTools::SupportedEncodersLoader encodersLoader;
		ConverterOptions::SupportedEncoders encoders;
															//todo test if ffmpeg exist
		//bool res =
		encodersLoader.scan(encoders, ffmpeg);	//todo error message

		//ConverterOptions::FFpreset ffpreset(ffpresetPath);

		ConverterOptions::OptionsLoaderXml optionsLoaderFromXml(xmlFilePath, encoders, ffpresetPath);

		ConverterOptions::OptionsDatabase optionsDatabase(&optionsLoaderFromXml);

		Profile::Profiles profiles;

		Profile::ProfileLoader loader;
		loader.load(profilesFolder, profiles);

		Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("data/model5.glade");

		converterGui = new Gui::ConverterGui(optionsDatabase, builder, profiles);
		converterGui->signalConvert().connect(sigc::mem_fun(*this, &OniboConverter::convert));
		Gtk::Main::run(converterGui->getWindow());
	}
};

int main(int argc, char *argv[]) {
	OniboConverter oniboConverter;
	oniboConverter.run(argc, argv);
	return 0;
}
