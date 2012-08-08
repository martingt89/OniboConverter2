/*
 * convertergui.cpp
 *
 *  Created on: 7.8.2012
 *      Author: martint
 */

#include "convertergui.h"

#include <iostream> //todo remove

namespace Gui {

static const int MAIN_SCREEN_PAGE = 0;
static const int CONFIG_SCREEN_PAGE = 1;

ConverterGui::ConverterGui(ConverterOptions::OptionsDatabase &database,
		const Glib::RefPtr<Gtk::Builder>& refGlade) :
		database(database), mainSettings(database, refGlade) {
	refGlade->get_widget("converterMainWindow", mainWindow);
	refGlade->get_widget("mainNotebook", mainNotebook);
	refGlade->get_widget("settingsButton", settingsButton);
	refGlade->get_widget("okSettingsButton", okSettingsButton);
	refGlade->get_widget("cancelSettingsButton", cancelSettingsButton);

	settingsButton->signal_clicked().connect(sigc::mem_fun(*this, &ConverterGui::settingsButtonClicked));
	okSettingsButton->signal_clicked().connect(sigc::mem_fun(*this, &ConverterGui::okSettingsButtonClicked));
	cancelSettingsButton->signal_clicked().connect(
			sigc::mem_fun(*this, &ConverterGui::cancelSettingsButtonClicked));

	//todo mainSettings signal
}

ConverterGui::~ConverterGui() {
	// TODO Auto-generated destructor stub
}

void ConverterGui::setAvailableProfiles(const std::list<Profile>& availableProfiles) {

}

Gtk::Window& ConverterGui::getWindow() {
	return *mainWindow;
}

void ConverterGui::settingsButtonClicked() {
	mainSettings.saveSettingsState();
	mainNotebook->set_current_page(CONFIG_SCREEN_PAGE);
}
void ConverterGui::okSettingsButtonClicked(){
	std::string message = "";
	bool isComplete = mainSettings.checkSettingsComplete(message);
	if(!isComplete){
		std::cout<<"Message: "<<message<<std::endl;
	}
	mainNotebook->set_current_page(MAIN_SCREEN_PAGE);
}
void ConverterGui::cancelSettingsButtonClicked(){
	mainSettings.restoreSettingsState();
	mainNotebook->set_current_page(MAIN_SCREEN_PAGE);
}
} /* namespace Gui */
