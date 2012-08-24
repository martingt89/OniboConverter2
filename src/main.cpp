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
#include "Gui/findffmpegdialog.h"
#include "MediaFile/mediafile.h"
#include "Profile/profile.h"
#include "Profile/profileloader.h"
#include "Converter/dispenser.h"
#include <iostream>					//todo remove
#include <unistd.h>

int getNumberOfCPU(){
	int cpus = sysconf(_SC_NPROCESSORS_ONLN);
	if(cpus <= 0){
		cpus = 1;
	}
	return cpus;
}

static const int numberOfThreads = getNumberOfCPU();

class OniboConverter{
private:
	Path ffpresetPath;
	Path xmlFilePath;
	Path ffmpeg;
	Path profilesFolder;
	Gui::ConverterGui* converterGui;
	Converter::Dispenser dispenser;
public:
	OniboConverter():
		ffpresetPath("ffpresets"),
		xmlFilePath("data/audio_video_settings.xml"),
		ffmpeg("ffmpeg"),
		profilesFolder("data/profiles"),
	converterGui(NULL), dispenser(numberOfThreads, false){}

	void convert(std::list<MediaFile::MediaFile*> mediaFiles){
//		for(MediaFile::MediaFile* file : mediaFiles){
//			if(!file->isSet()){
//				file->scanMediaFile();
//			}
//		}
		dispenser.processMediaFiles(mediaFiles);
	}

	bool run(Gtk::Main& kit){
		Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("data/model5.glade");

		ExternalTools::SupportedEncodersLoader encodersLoader;
		ConverterOptions::SupportedEncoders encoders;

		bool res = encodersLoader.scan(encoders, ffmpeg);

		if(!res){
			Gui::FindFFmpegDialog findDialog(builder, ffmpeg);
			kit.run(findDialog.getWindow());
			return findDialog.isNewStart();
		}else{
			ConverterOptions::OptionsLoaderXml optionsLoaderFromXml(xmlFilePath, encoders, ffpresetPath);

			ConverterOptions::OptionsDatabase optionsDatabase(&optionsLoaderFromXml);

			Profile::Profiles profiles;

			Profile::ProfileLoader loader;
			loader.load(profilesFolder, profiles);

			converterGui = new Gui::ConverterGui(optionsDatabase, builder, profiles);
			converterGui->signalConvert().connect(sigc::mem_fun(*this, &OniboConverter::convert));
			kit.run(converterGui->getWindow());
		}
		return false;
	}
};

int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);
	OniboConverter oniboConverter;
	bool repeat = false;
	do{
		repeat = oniboConverter.run(kit);
	}while(repeat);

	return 0;
}
