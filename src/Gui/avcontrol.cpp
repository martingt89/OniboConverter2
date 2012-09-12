/*
 * mainsettings.cpp
 *
 *  Created on: 7.8.2012
 *      Author: martint
 */

#include "avcontrol.h"
#include "../systemsettings.h"
#include "../Xml/profilegenerator.h"
#include <glibmm/i18n.h>

namespace Gui {

const static std::string CUSTOM_PROFILE = _("--- custom profile ---");

AVControl::AVControl(MediaElement::ElementsDB& elementsDB,
		const Glib::RefPtr<Gtk::Builder>& refGlade,
		const Profile::Profiles& profiles) : elementsDB(elementsDB), profiles(profiles),
				videoControlGui(elementsDB, refGlade),
				audioControlGui(elementsDB, refGlade),
				containers(refGlade, "containres"), profilesComboBox(refGlade, "profilesComboBox"),
				settingsDialog(refGlade), profileNameDialog(refGlade){

	multiPassState = false;
	isEnabledSignal = true;
	isUserInput = true;

	refGlade->get_widget("manualSettingsButton", manualSettingsButton);
	refGlade->get_widget("saveProfileAsButton", saveProfileAsButton);

	initContainers(elementsDB, containers);
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
		message = _("Container is not set");
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
std::string AVControl::getContainerName(){
	return containers.get_active_row_item().getName();
}
void AVControl::userInput(){
	if(isUserInput){
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
		MediaElement::Container container;
		if(profilesComboBox.get_active_row_item().getContainer(container)){
			containers.set_active_text(container.readableForm());
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
	Profile::Profile newProfile(name);
	newProfile.setContainer(containers.get_active_row_item());

	videoControlGui.getNewProfile(newProfile);
	audioControlGui.getNewProfile(newProfile);
	settingsDialog.getNewProfile(newProfile);

	profilesComboBox.append(name, newProfile);
	profilesComboBox.save_actual_state();
	Path userProfilesPath = SystemSettings::getInstance()->getUserProfilesPath();
	Xml::ProfileGenerator generator(userProfilesPath);

	generator.generateFile(Profile::Configuration(newProfile, elementsDB));
}
Profile::Profile AVControl::getTmpProfile(){
	Profile::Profile newProfile("tmp");
	newProfile.setContainer(containers.get_active_row_item());

	videoControlGui.getNewProfile(newProfile);
	audioControlGui.getNewProfile(newProfile);
	settingsDialog.getNewProfile(newProfile);
	return newProfile;
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
void AVControl::initContainers(MediaElement::ElementsDB& elementsDB,
		ComboBoxExt<MediaElement::Container> &containers){
	std::list<MediaElement::Container> cont = elementsDB.getContainers().getContainers();
	for(auto container : cont){
		containers.append(container.readableForm(), container);
	}
}
void AVControl::initProfiles(const Profile::Profiles& profiles,
		ComboBoxExt<Profile::Profile> &profilesComboBox){
	profilesComboBox.append(CUSTOM_PROFILE);
	profilesComboBox.set_active_row_number(0);
	auto profileList = profiles.getProfiles();
	for(auto profile : profileList){
		profilesComboBox.append(profile.getName(), profile);
	}
}
} /* namespace Gui */
