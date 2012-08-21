/*
 * convertergui.cpp
 *
 *  Created on: 7.8.2012
 *      Author: martint
 */

#include "convertergui.h"

#include "../MediaFile/mediafile.h"

namespace Gui {

static const int MAIN_SCREEN_PAGE = 0;
static const int CONFIG_SCREEN_PAGE = 1;

ConverterGui::ConverterGui(ConverterOptions::OptionsDatabase &database,
		const Glib::RefPtr<Gtk::Builder>& refGlade,
		const Profile::Profiles& profiles) :
		database(database), mainSettings(database, refGlade, profiles),
		destinationControl(refGlade), fileControl(refGlade), convertWindow(refGlade),
		warningDialog("Settings are not complete", false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK, true){

	refGlade->get_widget("converterMainWindow", mainWindow);
	refGlade->get_widget("mainNotebook", mainNotebook);
	refGlade->get_widget("settingsButton", settingsButton);
	refGlade->get_widget("okSettingsButton", okSettingsButton);
	refGlade->get_widget("cancelSettingsButton", cancelSettingsButton);
	refGlade->get_widget("convertButton", convertButton);

	settingsButton->signal_clicked().connect(sigc::mem_fun(*this, &ConverterGui::settingsButtonClicked));
	okSettingsButton->signal_clicked().connect(sigc::mem_fun(*this, &ConverterGui::okSettingsButtonClicked));
	cancelSettingsButton->signal_clicked().connect(
			sigc::mem_fun(*this, &ConverterGui::cancelSettingsButtonClicked));
	convertButton->signal_clicked().connect(sigc::mem_fun(*this, &ConverterGui::convertButtonClicked));
}

ConverterGui::~ConverterGui() {
	delete mainWindow;
	delete mainNotebook;
	delete settingsButton;
	delete okSettingsButton;
	delete cancelSettingsButton;
}

void ConverterGui::setAvailableProfiles(const std::list<Profile::Profile>& availableProfiles) {

}

Gtk::Window& ConverterGui::getWindow() {
	return *mainWindow;
}
sigc::signal<void, std::list<MediaFile::MediaFile*> >& ConverterGui::signalConvert(){
	return convertEvent;
}
void ConverterGui::settingsButtonClicked() {
	mainSettings.saveSettingsState();
	mainNotebook->set_current_page(CONFIG_SCREEN_PAGE);
}

void ConverterGui::showWarningDialog(const std::string& title, const std::string& message) {
	warningDialog.set_title(title);
	warningDialog.set_message(title);
	warningDialog.set_secondary_text(message, false);
	warningDialog.run();
	warningDialog.hide();
}

void ConverterGui::okSettingsButtonClicked() {
	std::string message = "";
	bool isComplete = mainSettings.checkSettingsComplete(message);
	if(isComplete){
		mainNotebook->set_current_page(MAIN_SCREEN_PAGE);
	}else{
		showWarningDialog("Settings are not complete", message);
	}
}
void ConverterGui::cancelSettingsButtonClicked(){
	mainSettings.restoreSettingsState();
	mainNotebook->set_current_page(MAIN_SCREEN_PAGE);
}
void ConverterGui::convertButtonClicked(){
	auto files = fileControl.getAllFiles();
	if(files.size() == 0){
		showWarningDialog("No file to processing", "Please add files");
		return;
	}
	std::string message = "";
	bool isComplete = mainSettings.checkSettingsComplete(message);
	if(!isComplete){
		settingsButtonClicked();
		showWarningDialog("Settings are not complete", message);
		return;
	}
	convertFilesList.clear();

	for(FileControl::PathWithFileId path : files){	//todo add filters support
		MediaFile::MediaFile* mediaFile = new MediaFile::MediaFile(path.path, path.id);
		mediaFile->setSettingsList(mainSettings.getConvertArguments());
		mediaFile->clearConvertStatus();
		convertFilesList.push_back(mediaFile);
	}
	convertEvent(convertFilesList);
	sigc::connection conn = Glib::signal_timeout().connect(sigc::mem_fun(*this,
            &ConverterGui::convertTimer), 1000);
}
bool ConverterGui::convertTimer(){
	CppExtension::HashMap<int, MediaFile::MediaFile*> files;
	for(auto file : convertFilesList){
		files.set(file->getFileId(), file);
	}
	convertWindow.display(files);
	return true;
}
} /* namespace Gui */
