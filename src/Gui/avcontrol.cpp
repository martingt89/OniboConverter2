/*
 * mainsettings.cpp
 *
 *  Created on: 7.8.2012
 *      Author: martint
 */

#include "avcontrol.h"
#include <iostream> //todo remove
namespace Gui {

AVControl::AVControl(ConverterOptions::OptionsDatabase &database,
		const Glib::RefPtr<Gtk::Builder>& refGlade) : database(database),
				videoSettingsGui(database, refGlade), containers(refGlade, "containres") {

	multiPassState = false;
	isEnabledSignal = true;
	isUserInput = true;

	initContainers(database, containers);
	videoSettingsGui.disableSettings();

	containers.signal_changed().connect(sigc::mem_fun(*this, &AVControl::containerChanged));
	videoSettingsGui.signalUserInput().connect(sigc::mem_fun(*this, &AVControl::userInput));

	isUserInput = false;
	containers.set_active_row_number(0);
	isUserInput = true;
}

AVControl::~AVControl() {
	// TODO Auto-generated destructor stub
}

bool AVControl::checkSettingsComplete(std::string& message){
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
void AVControl::saveSettingsState(){
	containers.save_actual_state();
	videoSettingsGui.saveSettingsState();
}
void AVControl::restoreSettingsState(){
	isEnabledSignal = false;
	containers.restor_saved_state();
	videoSettingsGui.restoreSettingsState();
	isEnabledSignal = true;
}
void AVControl::userInput(){
	if(isUserInput){
		std::cout<<"user input"<<std::endl;
	}
}
void AVControl::containerChanged(){
	if(isEnabledSignal){
		isEnabledSignal = false;
		if(containers.isSelectedActivableRow()){
			videoSettingsGui.videoContainerChanged(containers.get_active_row_item());
		}
		userInput();
		isEnabledSignal = true;
	}
}
void AVControl::initContainers(ConverterOptions::OptionsDatabase &database,
		ComboBoxExt<ConverterOptions::Container> &containers){
	std::list<ConverterOptions::Container> cont = database.getContainers().getContainers();
	for(auto containerIter = cont.begin(); containerIter!= cont.end(); ++containerIter){
		containers.append(containerIter->getName(), *containerIter);
	}
}
} /* namespace Gui */
