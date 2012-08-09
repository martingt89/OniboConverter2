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
	isEnabledSignal = true;

	initContainers(database, containers);
	videoSettingsGui.disableSettings();

	containers.signal_changed().connect(sigc::mem_fun(*this, &MainSettings::containerChanged));
	//videoSettingsGui.signalUserInput().connect(sigc::mem_fun(*this, &MainSettings::userInput));
}

MainSettings::~MainSettings() {
	// TODO Auto-generated destructor stub
}

bool MainSettings::checkSettingsComplete(std::string& message){
	message = "";
	if(!containers.isSelectedActivableRow()){
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
	videoSettingsGui.saveSettingsState();
}
void MainSettings::restoreSettingsState(){
	isEnabledSignal = false;
	containers.restor_saved_state();
	videoSettingsGui.restoreSettingsState();
	isEnabledSignal = true;
}
void MainSettings::userInput(){
//	std::cout<<"user input"<<std::endl;
}
void MainSettings::containerChanged(){
	if(isEnabledSignal){
		isEnabledSignal = false;
		if(containers.isSelectedActivableRow()){
			videoSettingsGui.videoContainerChanged(containers.get_active_row_item());
		}
		userInput();
		isEnabledSignal = true;
	}
}
void MainSettings::initContainers(ConverterOptions::OptionsDatabase &database,
		ComboBoxExt<ConverterOptions::Container> &containers){
	std::list<ConverterOptions::Container> cont = database.getContainers().getContainers();
	for(auto containerIter = cont.begin(); containerIter!= cont.end(); ++containerIter){
		containers.append(containerIter->getName(), *containerIter);
	}
}
} /* namespace Gui */
