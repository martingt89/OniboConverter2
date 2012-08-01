/*
 * guicontrols.cpp
 *
 *  Created on: 29.7.2012
 *      Author: martint
 */

#include "guicontrols.h"
#include "Video/globalvideosettings.h"

namespace Gui {

GuiControls::GuiControls(ConverterOptions::OptionsDatabase &database,
		const Glib::RefPtr<Gtk::Builder>& refGlade): database(database), refGlade(refGlade){
	refGlade->get_widget("converterWindow",converterWindow);
	refGlade->get_widget("outputPath",outputPath);
	refGlade->get_widget("outputPathButton",outputPathButton);
	refGlade->get_widget("containers",containers);
	refGlade->get_widget("profiles",profiles);
	settingsDialog = new SettingsDialog(refGlade);
	videoControls = new GlobalVideoSettings(database, refGlade, *settingsDialog);
	audioControls = 0;

	setContainers(*containers, database.getContainers().getContainers());
	addCustomProfile(*profiles);

	containers->signal_changed().connect(sigc::mem_fun(*this, &GuiControls::containerChanged));
	videoControls->signalUserInput().connect(sigc::mem_fun(*this, &GuiControls::setCustomProfile));
	//audioControls->signalUserInput().connect(sigc::mem_fun(*this, &GuiControls::setCustomProfile));
}

GuiControls::~GuiControls() {
	delete converterWindow;
	delete outputPath;
	delete outputPathButton;
	delete containers;
	delete profiles;
	delete settingsDialog;
	delete videoControls;
}

void GuiControls::setAvailableProfiles(const std::list<Profile>& availableProfiles){
	this->availableProfiles = availableProfiles;
}
Gtk::Window& GuiControls::getProgramWindow(){
	return *converterWindow;
}
//=======================================================================================
void GuiControls::setCustomProfile(){
	profiles->set_active(0);
}
void GuiControls::setContainers(Gtk::ComboBoxText& containers, std::list<ConverterOptions::Container> items){
	for(auto itemsIter = items.begin(); itemsIter != items.end(); ++itemsIter){
		containers.append(itemsIter->getName());
	}
}
void GuiControls::addCustomProfile(Gtk::ComboBoxText& profiles){
	profiles.append("Custom profile");
	profiles.set_active(0);
}
void GuiControls::containerChanged(){
	if(containers->get_active_row_number() < 0){
		return;
	}
	std::string containerName = containers->get_active_text();
	ConverterOptions::Container container = database.getContainers().getContainerByName(containerName);
	videoControls->setActiveContainer(container);
	//audioControls->setActiveContainer(containerName); //todo implement
}
} /* namespace Gui */
