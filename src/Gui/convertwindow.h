/*
 * convertwindow.h
 *
 *  Created on: 21.8.2012
 *      Author: martint
 */

#ifndef CONVERTWINDOW_H_
#define CONVERTWINDOW_H_

#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/spinner.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
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
	ConvertWindow(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~ConvertWindow();
	void display(CppExtension::HashMap<int, MediaFile::MediaFile*> files);
private:
	Gtk::Window* convertWindow;
	Gtk::Button* closeOkConvertButton;
	Gtk::Spinner* workingIndicator;
	Gtk::TreeView* convertTreeView;
	Glib::RefPtr<Gtk::ListStore> convertTreeModel;
	Glib::RefPtr<Gtk::TreeView::Selection> convertSelection;
};

} /* namespace Gui */
#endif /* CONVERTWINDOW_H_ */
