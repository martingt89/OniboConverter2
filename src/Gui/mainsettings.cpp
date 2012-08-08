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
				videoSettingsGui(database, refGlade), containers(refGlade, "containres") {

	multiPassState = false;

	initContainers(database, containers);
	videoSettingsGui.disableSettings();

	containers.signal_changed().connect(sigc::mem_fun(*this, &MainSettings::containerChanged));
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
void MainSettings::containerChanged(){
	videoSettingsGui.videoContainerChanged(containers.get_active_row_item());
}
void MainSettings::initContainers(ConverterOptions::OptionsDatabase &database,
		ComboBoxExt<ConverterOptions::Container> &containers){
	std::list<ConverterOptions::Container> cont = database.getContainers().getContainers();
	for(auto containerIter = cont.begin(); containerIter!= cont.end(); ++containerIter){
		containers.append(containerIter->getName(), *containerIter);
	}
}
} /* namespace Gui */
