/*
 * manualsettingscontrol.h
 *
 *  Created on: 18.8.2012
 *      Author: martint
 */

#ifndef MANUALSETTINGSCONTROL_H_
#define MANUALSETTINGSCONTROL_H_

#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/entry.h>
#include <gtkmm/dialog.h>
#include "../Profile/profile.h"

namespace Gui {

class ManualSettingsControl {
private:
	struct ManualSettingsBackup{
		std::string command;
		std::string args;
		bool operator==(const ManualSettingsBackup& second){
			return command == second.command && args == second.args;
		}
	};
	class ModelColumns: public Gtk::TreeModel::ColumnRecord {
	public:
		ModelColumns() {
			add(command);
			add(args);
		}

		Gtk::TreeModelColumn<Glib::ustring> command;
		Gtk::TreeModelColumn<Glib::ustring> args;
	};
	ModelColumns modelColumns;
public:
	ManualSettingsControl(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~ManualSettingsControl();
	bool start();
	void saveSettingsState();
	void restoreSettingsState();
	void setActiveProfile(const Profile::Profile& activeProfile);
	Converter::ConvertSettingsList getConvertArguments() const;
private:
	void addCommandClicked();
	void removecommandClicked();
	void editCommandClicked();
	void saveSettings(std::list<ManualSettingsBackup>& targate);
	void restorSettings(const std::list<ManualSettingsBackup>& source);
	bool isSameSettings(
			const std::list<ManualSettingsBackup>& first, const std::list<ManualSettingsBackup>& second);
	Gtk::Dialog* manualSettingsDialog;
	Gtk::Button* addCommand;
	Gtk::Button* removeCommand;
	Gtk::Button* editCommand;
	Gtk::Entry* commandEntry;
	Gtk::Entry* argsEntry;
	//
	Gtk::TreeView* commandTreeView;
	Glib::RefPtr<Gtk::ListStore> commandTreeModel;
	Glib::RefPtr<Gtk::TreeView::Selection> commandSelection;
	//
	std::list<ManualSettingsBackup> internalState;
	std::list<ManualSettingsBackup> globalState;
};

} /* namespace Gui */
#endif /* MANUALSETTINGSCONTROL_H_ */
