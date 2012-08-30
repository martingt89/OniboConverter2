/*
 * convertergui.cpp
 *
 *  Created on: 7.8.2012
 *      Author: martint
 */

#include "convertergui.h"

#include "../MediaFile/mediafile.h"
#include <iostream>

namespace Gui {

static const int MAIN_SCREEN_PAGE = 0;
static const int CONFIG_SCREEN_PAGE = 1;
static const int INFO_SCREEN_PAGE = 2;

ConverterGui::ConverterGui(ConverterOptions::OptionsDatabase &database,
		const Glib::RefPtr<Gtk::Builder>& refGlade,
		const Profile::Profiles& profiles) :
		database(database), mainSettings(database, refGlade, profiles),
		destinationControl(refGlade), fileControl(refGlade), infoControl(refGlade), overwrite(refGlade),
		warningDialog("Settings are not complete", false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK, true){

	refGlade->get_widget_derived("convertWindow", convertWindow);
	overwrite.setConvertWindow(convertWindow);
	refGlade->get_widget("converterMainWindow", mainWindow);
	refGlade->get_widget("mainNotebook", mainNotebook);
	refGlade->get_widget("settingsButton", settingsButton);
	refGlade->get_widget("okSettingsButton", okSettingsButton);
	refGlade->get_widget("cancelSettingsButton", cancelSettingsButton);
	refGlade->get_widget("convertButton", convertButton);
	refGlade->get_widget("returnFromInfo", returnFromInfo);

	mainWindow->signal_key_release_event().connect(sigc::mem_fun(*this, &ConverterGui::onKeyRelease));
	settingsButton->signal_clicked().connect(sigc::mem_fun(*this, &ConverterGui::settingsButtonClicked));
	okSettingsButton->signal_clicked().connect(sigc::mem_fun(*this, &ConverterGui::okSettingsButtonClicked));
	cancelSettingsButton->signal_clicked().connect(
			sigc::mem_fun(*this, &ConverterGui::cancelSettingsButtonClicked));
	convertButton->signal_clicked().connect(sigc::mem_fun(*this, &ConverterGui::convertButtonClicked));
	returnFromInfo->signal_clicked().connect(sigc::mem_fun(*this, &ConverterGui::returnInfoClicked));
	fileControl.signalInfo().connect(sigc::mem_fun(*this, &ConverterGui::fileInfoEvent));
	fileControl.signalDelete().connect(sigc::mem_fun(*this, &ConverterGui::fileDeleteEvent));
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
	for(auto file : convertFilesList){
		delete file;
	}
	convertFilesList.clear();

	for(FileControl::PathWithFileId path : files){
		MediaFile::MediaFile* mediaFile = NULL;
		if(idToMediaFile.isExistKey(path.id)){
			mediaFile = new MediaFile::MediaFile(*idToMediaFile.get(path.id));
		}else{
			mediaFile = new MediaFile::MediaFile(path.path, path.id);
		}
		mediaFile->setSettingsList(mainSettings.getConvertArguments());
		mediaFile->setDestinationPath(destinationControl.getDestinationPath());
		mediaFile->setContainerName(mainSettings.getContainerName());
		mediaFile->clearConvertStatus();
		convertFilesList.push_back(mediaFile);
	}
	convertEvent(convertFilesList);
	convertTimer();
	sigc::connection conn = Glib::signal_timeout().connect(sigc::mem_fun(*this,
            &ConverterGui::convertTimer), 1000);

}
bool ConverterGui::onKeyRelease(GdkEventKey* event){
	if(event->keyval == GDK_KEY_Escape){
		if(mainNotebook->get_current_page() == CONFIG_SCREEN_PAGE ){
			cancelSettingsButtonClicked();
		}else if(mainNotebook->get_current_page() == INFO_SCREEN_PAGE){
			returnInfoClicked();
		}
	}
	return false;
}
void ConverterGui::fileInfoEvent(const Gui::FileControl::PathWithFileId& file){
	if(!idToMediaFile.isExistKey(file.id)){
		auto mediaFile = new MediaFile::MediaFile(file.path, file.id);
		idToMediaFile.set(file.id, mediaFile);
		mediaFile->scanMediaFile();
	}
	auto* mediaFile = idToMediaFile.get(file.id);
	if(mediaFile->isValid()){
		infoControl.show(mediaFile);
		mainNotebook->set_current_page(INFO_SCREEN_PAGE);
	}else{
		showWarningDialog("File is not supported", "File is not supported");
	}
}
void ConverterGui::fileDeleteEvent(const Gui::FileControl::PathWithFileId& file){
	bool exist = false;
	MediaFile::MediaFile* mediaFile = idToMediaFile.get(file.id, exist);
	if(exist){
		delete mediaFile;
		idToMediaFile.remove(file.id);
	}
}
void ConverterGui::returnInfoClicked(){
	mainNotebook->set_current_page(MAIN_SCREEN_PAGE);
}
bool ConverterGui::convertTimer(){
	CppExtension::HashMap<int, MediaFile::MediaFile*> files;
	bool running = false;
	if(convertWindow->isAbort()){
		for(auto file : convertFilesList){
			file->abort();
		}
	}
	for(auto file : convertFilesList){
		if(!file->isEnded()){
			running = true;
		}
		files.set(file->getFileId(), file);
		if(file->getConvertState() == MediaFile::MediaFile::OVERWRITE){
			overwrite.addFile(file);
		}
	}
	convertWindow->display(files, !running);
	return running;
}
} /* namespace Gui */
