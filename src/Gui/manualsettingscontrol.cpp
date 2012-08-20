/*
 * manualsettingscontrol.cpp
 *
 *  Created on: 18.8.2012
 *      Author: martint
 */

#include "manualsettingscontrol.h"
#include <gtkmm/stock.h>
namespace Gui {

ManualSettingsControl::ManualSettingsControl(const Glib::RefPtr<Gtk::Builder>& refGlade) {
	refGlade->get_widget("manualSettingsDialog", manualSettingsDialog);
	refGlade->get_widget("addCommand", addCommand);
	refGlade->get_widget("removeCommand", removeCommand);
	refGlade->get_widget("editCommand", editCommand);
	refGlade->get_widget("commandEntry", commandEntry);
	refGlade->get_widget("argsEntry", argsEntry);
	refGlade->get_widget("commandTreeView", commandTreeView);

	manualSettingsDialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	manualSettingsDialog->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

	commandTreeModel = Gtk::ListStore::create(modelColumns);
	commandTreeView->set_model(commandTreeModel);
	commandSelection = commandTreeView->get_selection();
	commandTreeView->append_column("Command", modelColumns.command);
	commandTreeView->append_column("Arguments", modelColumns.args);

	addCommand->signal_clicked().connect(sigc::mem_fun(*this, &ManualSettingsControl::addCommandClicked));
	removeCommand->signal_clicked().connect(
			sigc::mem_fun(*this, &ManualSettingsControl::removecommandClicked)
	);
	editCommand->signal_clicked().connect(sigc::mem_fun(*this, &ManualSettingsControl::editCommandClicked));
}

ManualSettingsControl::~ManualSettingsControl() {
	delete manualSettingsDialog;
	delete addCommand;
	delete removeCommand;
	delete editCommand;
	delete commandEntry;
	delete argsEntry;
	delete commandTreeView;
}
bool ManualSettingsControl::start(){
	saveSettings(internalState);
	argsEntry->set_text("");
	commandEntry->set_text("");
	int res = manualSettingsDialog->run();
	manualSettingsDialog->hide();
	if(res == Gtk::RESPONSE_OK){
		std::list<ManualSettingsBackup> actualState;
		saveSettings(actualState);
		bool isSame = isSameSettings(internalState, actualState);
		return !isSame;
	}else{
		restorSettings(internalState);
		return false;
	}
}
void ManualSettingsControl::saveSettingsState(){
	saveSettings(globalState);
}
void ManualSettingsControl::restoreSettingsState(){
	restorSettings(globalState);
}
void ManualSettingsControl::setActiveProfile(const Profile::Profile& activeProfile){
	std::list<Profile::Profile::ManualSettings> profileSettings;
	activeProfile.getManualSettings(profileSettings);
	commandTreeModel->clear();
	for(auto item : profileSettings){
		Gtk::TreeModel::Row row = *(commandTreeModel->append());
		row[modelColumns.command] = item.command;
		std::string argString;
		for(auto arg : item.args){
			if(argString.size() == 0){
				argString = arg;
			}else{
				argString += " "+arg;
			}
		}
		row[modelColumns.args] = argString;
	}

}
Converter::ConvertSettingsList ManualSettingsControl::getConvertArguments() const{
	Converter::ConvertSettingsList args;
	//todo implement
	return args;
}
//=============================================================
void ManualSettingsControl::addCommandClicked(){
	Gtk::TreeModel::Row row = *(commandTreeModel->append());
	row[modelColumns.command] = commandEntry->get_text();
	row[modelColumns.args] = argsEntry->get_text();
}
void ManualSettingsControl::removecommandClicked(){
	Gtk::TreeModel::iterator iter = commandSelection->get_selected();
	if(iter){
		commandTreeModel->erase(iter);
	}
}
void ManualSettingsControl::editCommandClicked(){
	Gtk::TreeModel::iterator iter = commandSelection->get_selected();
	if(iter){
		Gtk::TreeModel::Row row = *iter;
		commandEntry->set_text((Glib::ustring)row[modelColumns.command]);
		argsEntry->set_text((Glib::ustring)row[modelColumns.args]);
		commandTreeModel->erase(iter);
	}
}
void ManualSettingsControl::saveSettings(std::list<ManualSettingsBackup>& targate) {
	targate.clear();
	auto children = commandTreeModel->children();
	if (children) {
		for (auto iter = children.begin(); iter != children.end(); ++iter) {
			Gtk::TreeModel::Row row = *iter;
			ManualSettingsBackup backup;
			backup.command = (Glib::ustring) row[modelColumns.command];
			backup.args = (Glib::ustring) row[modelColumns.args];
			targate.push_back(backup);
		}
	}
}
void ManualSettingsControl::restorSettings(const std::list<ManualSettingsBackup>& source){
	commandTreeModel->clear();
	for(auto backup : source){
		Gtk::TreeModel::Row row = *(commandTreeModel->append());
		row[modelColumns.command] = backup.command;
		row[modelColumns.args] = backup.args;
	}
}
bool ManualSettingsControl::isSameSettings(
		const std::list<ManualSettingsBackup>& first,
		const std::list<ManualSettingsBackup>& second){

	if(first.size() == second.size()){
		std::list<ManualSettingsBackup> localCopy = second;
		for(ManualSettingsBackup item : first){
			localCopy.remove(item);
		}
		return localCopy.empty();
	}
	return false;
}
} /* namespace Gui */
