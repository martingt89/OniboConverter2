/* ---------------------------------------------------------------------------
** Author: Martin Geier
** convertergui.cpp is part of OniboConverter2.
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

#include "convertergui.h"

#include <glibmm/main.h>
#include <sigc++/connection.h>
#include "../MediaFile/mediafile.h"

namespace Gui {

static const int MAIN_SCREEN_PAGE = 0;
static const int CONFIG_SCREEN_PAGE = 1;
static const int INFO_SCREEN_PAGE = 2;
static const int CONVERT_SCREEN_PAGE = 3;

ConverterGui::ConverterGui(MediaElement::ElementsDB& elementsDB,
		const Glib::RefPtr<Gtk::Builder>& refGlade,
		Profile::Profiles& profiles,
		Gui::MainWindow* mainWindow) :
		avControl(elementsDB, refGlade, profiles),
		destinationControl(refGlade), fileControl(refGlade), infoControl(refGlade),
		overwrite(refGlade), convertWindow(refGlade), settingsDialog(refGlade), mainWindow(mainWindow),
		warningDialog("Settings are not complete", false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK, true),
		unsuportedEncoders(refGlade, elementsDB), inportExport(refGlade, elementsDB){

	refGlade->get_widget("mainNotebook", mainNotebook);
	refGlade->get_widget("settingsButton", settingsButton);
	refGlade->get_widget("okSettingsButton", okSettingsButton);
	refGlade->get_widget("cancelSettingsButton", cancelSettingsButton);
	refGlade->get_widget("convertButton", convertButton);
	refGlade->get_widget("returnFromInfo", returnFromInfo);
	refGlade->get_widget("settingsMenuItem", settingsMenuItem);
	refGlade->get_widget("preferenceMenuItem", preferenceMenuItem);
	refGlade->get_widget("quitMenuItem", quitMenuItem);
	refGlade->get_widget("aboutMenuItem", aboutMenuItem);
	refGlade->get_widget("aboutDialog", aboutDialog);

	mainWindow->signal_key_release_event().connect(sigc::mem_fun(*this, &ConverterGui::onKeyRelease));
	settingsButton->signal_clicked().connect(sigc::mem_fun(*this, &ConverterGui::settingsButtonClicked));
	settingsMenuItem->signal_activate().connect(sigc::mem_fun(*this, &ConverterGui::settingsButtonClicked));
	okSettingsButton->signal_clicked().connect(sigc::mem_fun(*this, &ConverterGui::okSettingsButtonClicked));
	cancelSettingsButton->signal_clicked().connect(
			sigc::mem_fun(*this, &ConverterGui::cancelSettingsButtonClicked));
	convertButton->signal_clicked().connect(sigc::mem_fun(*this, &ConverterGui::convertButtonClicked));
	returnFromInfo->signal_clicked().connect(sigc::mem_fun(*this, &ConverterGui::returnToMainPage));
	fileControl.signalInfo().connect(sigc::mem_fun(*this, &ConverterGui::fileInfoEvent));
	fileControl.signalDelete().connect(sigc::mem_fun(*this, &ConverterGui::fileDeleteEvent));
	convertWindow.signalHide().connect(sigc::mem_fun(*this, &ConverterGui::returnToMainPage));
	mainWindow->signalClose().connect(sigc::mem_fun(*this, &ConverterGui::closeMainWindow));
	quitMenuItem->signal_activate().connect(sigc::mem_fun(*this, &ConverterGui::closeMainWindow));
	preferenceMenuItem->signal_activate().connect(sigc::mem_fun(settingsDialog, &Settings::UserSettingsDialog::start));
	aboutMenuItem->signal_activate().connect(sigc::mem_fun(*this, &ConverterGui::showAboutDialog));

	auto unssuported = elementsDB.getUnsuprtedEncoders();
	if(!unssuported.isEmpty() && !UserPreferences::getInstance()->isDisableShowUnEncoders()){
		unsuportedEncoders.show();
	}
	inportExport.setAVControl(&avControl);
	inportExport.setProfiles(&profiles);
}

ConverterGui::~ConverterGui() {
	delete mainNotebook;
	delete settingsButton;
	delete okSettingsButton;
	delete cancelSettingsButton;
}

sigc::signal<void, std::list<MediaFile::MediaFile*> >& ConverterGui::signalConvert(){
	return convertEvent;
}
void ConverterGui::closeMainWindow(){
	int currentPage = mainNotebook->get_current_page();
	if(currentPage == MAIN_SCREEN_PAGE){
		mainWindow->exit();
	}else if(currentPage == CONFIG_SCREEN_PAGE){
		cancelSettingsButtonClicked();
	}else if(currentPage == INFO_SCREEN_PAGE){
		returnToMainPage();
	}else if(currentPage == CONVERT_SCREEN_PAGE){
		convertWindow.stopConvertingSignal();
	}
}
void ConverterGui::settingsButtonClicked() {
	avControl.saveSettingsState();
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
	bool isComplete = avControl.checkSettingsComplete(message);
	if(isComplete){
		mainNotebook->set_current_page(MAIN_SCREEN_PAGE);
	}else{
		showWarningDialog("Settings are not complete", message);
	}
}
void ConverterGui::cancelSettingsButtonClicked(){
	avControl.restoreSettingsState();
	mainNotebook->set_current_page(MAIN_SCREEN_PAGE);
}
void ConverterGui::convertButtonClicked(){
	auto files = fileControl.getAllFiles();
	if(files.size() == 0){
		showWarningDialog("No file to processing", "Please add files");
		return;
	}
	std::string message = "";
	bool isComplete = avControl.checkSettingsComplete(message);
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
		mediaFile->setActualProfile(avControl.getTmpProfile());
		mediaFile->setDestinationPath(destinationControl.getDestinationPath());
		convertFilesList.push_back(mediaFile);
	}
	convertWindow.initConversion(convertFilesList, destinationControl.getDestinationPath());
	mainNotebook->set_current_page(CONVERT_SCREEN_PAGE);
	convertEvent(convertFilesList);

	sigc::connection conn = Glib::signal_timeout().connect(sigc::mem_fun(*this,
            &ConverterGui::convertTimer), 1000);
}
bool ConverterGui::onKeyRelease(GdkEventKey* event){
	if(event->keyval == GDK_KEY_Escape){
		if(mainNotebook->get_current_page() == INFO_SCREEN_PAGE){
			returnToMainPage();
		}
	}
	return false;
}
void ConverterGui::fileInfoEvent(const Gui::FileControl::PathWithFileId file){
	if(!idToMediaFile.isExistKey(file.id)){
		auto mediaFile = new MediaFile::MediaFile(file.path, file.id);
		idToMediaFile.set(file.id, mediaFile);
		mediaFile->getMediaInfo().scanMediaFile();
	}

	auto* mediaFile = idToMediaFile.get(file.id);
	if(mediaFile->getMediaInfo().getScanStatus() == MediaFile::MediaInfo::OK){
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
void ConverterGui::returnToMainPage(){
	mainNotebook->set_current_page(MAIN_SCREEN_PAGE);
}
bool ConverterGui::convertTimer(){
	CppExtension::HashMap<int, MediaFile::MediaFile*> files;
	bool running = false;
	if(convertWindow.isAbort()){
		for(auto file : convertFilesList){
			file->getMediaConvert()->abort();
		}
	}
	for(auto file : convertFilesList){
		if(!file->getMediaConvert()->isEnded()){
			running = true;
		}
		files.set(file->getFileId(), file);
		if(file->getMediaConvert()->getConvertState() == MediaFile::MediaConvert::OVERWRITE){
			overwrite.addFile(file);
		}
	}
	convertWindow.display(!running);
	return running;
}
void ConverterGui::showAboutDialog(){
	aboutDialog->run();
	aboutDialog->hide();
}
} /* namespace Gui */
