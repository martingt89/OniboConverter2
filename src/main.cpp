/* ---------------------------------------------------------------------------
** Author: Martin Geier
** main.cpp is part of OniboConverter2.
**
** OniboConverter2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
** -------------------------------------------------------------------------*/

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
		Path converter(SystemSettings::getInstance()->getGladeFilesFolder().getPath(), "converter.glade");
		Path dialogs(SystemSettings::getInstance()->getGladeFilesFolder().getPath(), "dialogs.glade");
		Path user_settings(SystemSettings::getInstance()->getGladeFilesFolder().getPath(), "user_settings.glade");
		//
		Glib::RefPtr<Gtk::Builder> builder;
		try{
			builder = Gtk::Builder::create_from_file(converter.getPath());
			builder->add_from_file(dialogs.getPath());
			builder->add_from_file(user_settings.getPath());
		}catch(const Glib::Exception& exception){
			std::cerr<<"Error: 'main.cpp' " <<exception.what()<<std::endl;
			_exit(-1);
		}

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
