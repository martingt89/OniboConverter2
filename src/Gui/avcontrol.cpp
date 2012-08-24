/*
 * mainsettings.cpp
 *
 *  Created on: 7.8.2012
 *      Author: martint
 */

#include "avcontrol.h"
#include "../Xml/profiletoxmlconverter.h"
namespace Gui {

const static std::string CUSTOM_PROFILE = "--- custom profile ---";

AVControl::AVControl(ConverterOptions::OptionsDatabase &database,
		const Glib::RefPtr<Gtk::Builder>& refGlade,
		const Profile::Profiles& profiles) : database(database), profiles(profiles),
				videoControlGui(database, refGlade), audioControlGui(database, refGlade),
				containers(refGlade, "containres"), profilesComboBox(refGlade, "profilesComboBox"),
				settingsDialog(refGlade), profileNameDialog(refGlade){

	multiPassState = false;
	isEnabledSignal = true;
	isUserInput = true;

	refGlade->get_widget("manualSettingsButton", manualSettingsButton);
	refGlade->get_widget("saveProfileAsButton", saveProfileAsButton);

	initContainers(database, containers);
	initProfiles(profiles, profilesComboBox);
	videoControlGui.disableSettings();
	audioControlGui.disableSettings();

	containers.signal_changed().connect(sigc::mem_fun(*this, &AVControl::containerChanged));
	videoControlGui.signalUserInput().connect(sigc::mem_fun(*this, &AVControl::userInput));
	audioControlGui.signalUserInput().connect(sigc::mem_fun(*this, &AVControl::userInput));
	profilesComboBox.signal_changed().connect(sigc::mem_fun(*this, &AVControl::profileChanged));
	manualSettingsButton->signal_clicked().connect(sigc::mem_fun(*this, &AVControl::manualSettingsClicked));
	saveProfileAsButton->signal_clicked().connect(sigc::mem_fun(*this, &AVControl::saveProfileClicked));
	isUserInput = false;
	containers.set_active_row_number(0);
	isUserInput = true;
}

AVControl::~AVControl() {
	delete manualSettingsButton;
}

bool AVControl::checkSettingsComplete(std::string& message){
	message = "";
	if(!containers.isSelectedActivableRow()){
		message = "Container is not set";
		return false;
	}
	bool isSetVideo = videoControlGui.checkSettingsComplete(message);
	if(!isSetVideo){
		return false;
	}
	return audioControlGui.checkSettingsComplete(message);
}
void AVControl::saveSettingsState(){
	containers.save_actual_state();
	videoControlGui.saveSettingsState();
	audioControlGui.saveSettingsState();
	settingsDialog.saveSettingsState();
	profilesComboBox.save_actual_state();
}
void AVControl::restoreSettingsState(){
	isEnabledSignal = false;
	containers.restor_saved_state();
	videoControlGui.restoreSettingsState();
	audioControlGui.restoreSettingsState();
	settingsDialog.restoreSettingsState();
	profilesComboBox.restor_saved_state();
	isEnabledSignal = true;
}
Converter::ConvertSettingsList AVControl::getConvertArguments() const{
	Converter::ConvertSettingsList args;
	args.add(containers.get_active_row_item().getConvertArguments());
	args.add(videoControlGui.getConvertArguments());
	args.add(audioControlGui.getConvertArguments());
	args.add(settingsDialog.getConvertArguments());
	return args;
}
void AVControl::userInput(){
	if(isUserInput){
//		std::cout<<"user input"<<std::endl;
		profilesComboBox.set_active_row_number(0);	//set custom
	}
}
void AVControl::containerChanged(){
	if(isEnabledSignal){
		isEnabledSignal = false;
		if(containers.isSelectedActivableRow()){
			videoControlGui.containerChanged(containers.get_active_row_item());
			audioControlGui.containerChanged(containers.get_active_row_item());
		}
		userInput();
		isEnabledSignal = true;
	}
}
void AVControl::profileChanged(){
	if(isEnabledSignal){
		if(profilesComboBox.is_set_first()){
			return;
		}
		isUserInput = false;
		std::string containerName;
		if(profilesComboBox.get_active_row_item().getContainerName(containerName)){
			containers.set_active_text(containerName);
			videoControlGui.setActiveProfile(profilesComboBox.get_active_row_item());
			audioControlGui.setActiveProfile(profilesComboBox.get_active_row_item());
			settingsDialog.setActiveProfile(profilesComboBox.get_active_row_item());
		}else{
			containers.unset_active();
		}
		isUserInput = true;
	}
}
void AVControl::getNewProfile(const std::string& name){
	Profile::Profile newProfile;
	newProfile.addProperty(Profile::Profile::CONTAINER_OPT, containers.get_active_row_item().getName());
	videoControlGui.getNewProfile(newProfile);
	audioControlGui.getNewProfile(newProfile);
	settingsDialog.getNewProfile(newProfile);
	newProfile.addProperty(Profile::Profile::NAME_OPT, name);
	profilesComboBox.append(name, newProfile);
	profilesComboBox.save_actual_state();
	Xml::ProfileToXmlConverter converter;
	converter.convertToFile(newProfile);
}
void AVControl::manualSettingsClicked(){
	bool change = settingsDialog.start();
	if(change){
		userInput();
	}
}
void AVControl::saveProfileClicked(){
	std::string profileName;
	if(profileNameDialog.getName(profileName)){
		getNewProfile(profileName);
	}
}
void AVControl::initContainers(ConverterOptions::OptionsDatabase &database,
		ComboBoxExt<ConverterOptions::Container> &containers){
	std::list<ConverterOptions::Container> cont = database.getContainers().getContainers();
	for(auto containerIter = cont.begin(); containerIter!= cont.end(); ++containerIter){
		containers.append(containerIter->getName(), *containerIter);
	}
}
void AVControl::initProfiles(const Profile::Profiles& profiles,
		ComboBoxExt<Profile::Profile> &profilesComboBox){
	profilesComboBox.append(CUSTOM_PROFILE);
	profilesComboBox.set_active_row_number(0);
	for(auto profile : profiles){
		profilesComboBox.append(profile.getName(), profile);
	}
}
} /* namespace Gui */
