/*
 * mainsettings.cpp
 *
 *  Created on: 7.8.2012
 *      Author: martint
 */

#include "mainsettings.h"

namespace Gui {

MainSettings::MainSettings(ConverterOptions::OptionsDatabase &database,
		const Glib::RefPtr<Gtk::Builder>& refGlade) : database(database),
				videoSettingsGui(database, refGlade) {

	multiPassState = false;
	Gtk::ComboBoxText* _containers;
	refGlade->get_widget("containres", _containers);
	containers.set_comboboxtext_widget(_containers);

	initContainers(database, containers);
	//todo videoSettingsGui signal
}

MainSettings::~MainSettings() {
	// TODO Auto-generated destructor stub
}

bool MainSettings::checkSettingsComplete(std::string& message){
	message = "";
	if(!containers.isSet()){
		message = "Container is not set";
		return false;
	}
	bool isSetVideo = videoSettingsGui.checkSettingsComplete(message);
	if(!isSetVideo){
		return false;
	}
	//audio settings
	return true;
}
void MainSettings::saveSettingsState(){
	containers.save_actual_state();
	//multiPassState
	videoSettingsGui.saveSettingsState();
}
void MainSettings::restoreSettingsState(){
	//multiPassState
	containers.restor_saved_state();
	videoSettingsGui.restoreSettingsState();
}

void MainSettings::initContainers(ConverterOptions::OptionsDatabase &database,
		ComboBoxExt<ConverterOptions::Container> &containers){
	std::list<ConverterOptions::Container> cont = database.getContainers().getContainers();
	for(auto containerIter = cont.begin(); containerIter!= cont.end(); ++containerIter){
		containers.append(containerIter->getName(), *containerIter);
	}
}
} /* namespace Gui */
