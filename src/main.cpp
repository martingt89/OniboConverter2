/*
 * main.cpp
 *
 *  Created on: 18.7.2012
 *      Author: martint
 */

#include <gtkmm/main.h>
#include <gtkmm/builder.h>
#include <glibmm/i18n.h>

#include "CppExtension/path.h"
#include "ExternalTools/supportedencodersloader.h"
#include "Gui/convertergui.h"
#include "Gui/findffmpegdialog.h"
#include "Gui/mainwindow.h"
#include "MediaFile/mediafile.h"
#include "Profile/profile.h"
#include "Profile/profiles.h"
#include "Converter/dispenser.h"
#include "systemsettings.h"
#include "userpreferences.h"
#include "MediaElement/elementsdb.h"
#include "System/cpu.h"

#include <config.h>

#include <iostream>

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
		ffpresetPath = SystemSettings::getInstance()->getFFpresetFolder();
		xmlFilePath = SystemSettings::getInstance()->getXmlConfigFilePath();
		defaultProfilesFolder = SystemSettings::getInstance()->getDefaultProfilesPath();
		userprofilesFolder = SystemSettings::getInstance()->getUserProfilesPath();
	}

	void convert(std::list<MediaFile::MediaFile*> mediaFiles){
		int numberOfThreads = 1;
		if(UserPreferences::getInstance()->isAutomaticNumberOfCPU()){
			System::CPU cpu;
			numberOfThreads = cpu.getNumerOfThreads();
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

		ExternalTools::SupportedEncodersLoader encodersLoader;	//todo move to supported encoders
		ConverterOptions::SupportedEncoders encoders;

		bool res = encodersLoader.scan(encoders, extConverter);

		if(!res){
			Gui::FindFFmpegDialog findDialog(builder, extConverter);
			kit.run(findDialog.getWindow());
			return findDialog.isNewStart();
		}else{
			MediaElement::ElementsDB elementsDB;

			elementsDB.load(xmlFilePath, ffpresetPath, encoders);

			Profile::Profiles profiles(elementsDB);
			profiles.load();

			Gui::MainWindow* mainWindow;
			builder->get_widget_derived("mainWindow", mainWindow);
			mainWindow->show();

			converterGui = new Gui::ConverterGui(elementsDB, builder, profiles, mainWindow);
			converterGui->signalConvert().connect(sigc::mem_fun(*this, &OniboConverter::convert));
			kit.run();
		}
		return false;
	}
};

int main(int argc, char *argv[]) {
	bindtextdomain(GETTEXT_PACKAGE, DATADIR"/locale");
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);

	Gtk::Main kit(argc, argv);
	OniboConverter oniboConverter;
	bool repeat = false;
	do{
		repeat = oniboConverter.run(kit);
	}while(repeat);

	return 0;
}
