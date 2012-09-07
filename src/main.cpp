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
#include "Gui/mainwindow.h"
#include "MediaFile/mediafile.h"
#include "Profile/profile.h"
#include "Profile/profileloader.h"
#include "Converter/dispenser.h"
#include "globalsettings.h"
#include "userpreferences.h"
#include <unistd.h>

int getNumberOfCPU(){
	int cpus = sysconf(_SC_NPROCESSORS_ONLN);
	if(cpus <= 0){
		cpus = 1;
	}
	return cpus;
}

class OniboConverter{
private:
	Path ffpresetPath;
	Path xmlFilePath;
	Path extConverter;
	Path defaultProfilesFolder;
	Path userprofilesFolder;
	Gui::ConverterGui* converterGui;
	Converter::Dispenser dispenser;
public:
	OniboConverter(): converterGui(NULL){
		ffpresetPath = GlobalSettings::getInstance()->getFFpresetFolder();
		xmlFilePath = GlobalSettings::getInstance()->getXmlConfigFilePath();
		defaultProfilesFolder = GlobalSettings::getInstance()->getDefaultProfilesPath();
		userprofilesFolder = GlobalSettings::getInstance()->getUserProfilesPath();
	}

	void convert(std::list<MediaFile::MediaFile*> mediaFiles){
		int numberOfThreads = 1;
		if(UserPreferences::getInstance()->isAutomaticNumberOfCPU()){
			numberOfThreads = getNumberOfCPU();
		}else{
			numberOfThreads = UserPreferences::getInstance()->getNumerOfCPU();
		}
		bool enableFileMultithreading = UserPreferences::getInstance()->isMultithreadinForEncoders();
		dispenser.processMediaFiles(mediaFiles, numberOfThreads, enableFileMultithreading);
	}

	bool run(Gtk::Main& kit){
		extConverter = UserPreferences::getInstance()->getExtConverterPath();
		Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("data/converter.glade");
		builder->add_from_file("data/dialogs.glade");
		builder->add_from_file("data/user_settings.glade");

		ExternalTools::SupportedEncodersLoader encodersLoader;
		ConverterOptions::SupportedEncoders encoders;

		bool res = encodersLoader.scan(encoders, extConverter);

		if(!res){
			Gui::FindFFmpegDialog findDialog(builder, extConverter);
			kit.run(findDialog.getWindow());
			return findDialog.isNewStart();
		}else{
			ConverterOptions::OptionsLoaderXml optionsLoaderFromXml(xmlFilePath, encoders, ffpresetPath);

			ConverterOptions::OptionsDatabase optionsDatabase(&optionsLoaderFromXml);

			Profile::Profiles profiles;

			Profile::ProfileLoader loader;
			loader.load(defaultProfilesFolder, profiles);
			loader.load(userprofilesFolder, profiles);

			Gui::MainWindow* mainWindow;
			builder->get_widget_derived("mainWindow", mainWindow);
			mainWindow->show();

			converterGui = new Gui::ConverterGui(optionsDatabase, builder, profiles, mainWindow);
			converterGui->signalConvert().connect(sigc::mem_fun(*this, &OniboConverter::convert));
			kit.run();
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
