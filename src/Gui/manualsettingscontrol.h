/* ---------------------------------------------------------------------------
** Author: Martin Geier
** manualsettingscontrol.h is part of OniboConverter2.
**
** OniboConverter2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
** -------------------------------------------------------------------------*/

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
//	Converter::ConvertSettingsList getConvertArguments() const;
	void getNewProfile(Profile::Profile& newProfile);
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
