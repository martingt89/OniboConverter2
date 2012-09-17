/* ---------------------------------------------------------------------------
** Author: Martin Geier
** convertwindow.h is part of OniboConverter2.
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

#ifndef CONVERTWINDOW_H_
#define CONVERTWINDOW_H_

#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/dialog.h>
#include <gtkmm/button.h>
#include <gtkmm/spinner.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/textview.h>
#include <gtkmm/messagedialog.h>
#include "../MediaFile/mediafile.h"
namespace Gui {

class ConvertWindow {
private:
	class ModelColumns: public Gtk::TreeModel::ColumnRecord {
	public:

		ModelColumns() {
			add(fileID);
			add(name);
			add(time);
			add(percentage);
			add(state);
		}
		Gtk::TreeModelColumn<int> fileID;
		Gtk::TreeModelColumn<std::string> name;
		Gtk::TreeModelColumn<std::string> time;
		Gtk::TreeModelColumn<int> percentage;
		Gtk::TreeModelColumn<std::string> state;
	};
	ModelColumns modelColumns;
public:
	ConvertWindow(const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~ConvertWindow();
	void display(bool isEnd);
	bool isAbort();
	void initConversion(std::list<MediaFile::MediaFile*>& files, const Path& destination);
	sigc::signal<void>& signalHide();
	void stopConvertingSignal();

private:
	void closePage();
	void showDestination();
	void loadWidgets(const Glib::RefPtr<Gtk::Builder>& refGlade);
	void initConvertTreeView();
	void initStopDialog();
	void initOutputDialog();
	void infoConvertSignal();
	void fileTreeViewActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);

	bool abort;
	bool converting;

	Gtk::Dialog* convertOutputDialog;
	Gtk::TextView* convertOutputText;
	Gtk::Button* closeConvertButton;
	Gtk::Button* stopConvertButton;
	Gtk::Button* infoConvertButton;
	Gtk::Button* showDestinationButton;
	Gtk::Spinner* workingIndicator;
	Gtk::TreeView* convertTreeView;
	Gtk::Label* convertWindowMessage;
	Gtk::MessageDialog* stopConvertingDialog;
	Glib::RefPtr<Gtk::ListStore> convertTreeModel;
	Glib::RefPtr<Gtk::TreeView::Selection> convertSelection;
	sigc::signal<void> hideEvent;
	CppExtension::HashMap<int, MediaFile::MediaFile*> idToMediaFile;
	Path destination;
};

} /* namespace Gui */
#endif /* CONVERTWINDOW_H_ */
