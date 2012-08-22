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

class ConvertWindow : public Gtk::Window {
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
	ConvertWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~ConvertWindow();
	void display(CppExtension::HashMap<int, MediaFile::MediaFile*> files, bool isEnd);
protected:
	virtual void on_hide ();
private:
	Gtk::Window* convertWindow;
	Gtk::Button* closeConvertButton;
	Gtk::Button* okConvertButton;
	Gtk::Spinner* workingIndicator;
	Gtk::TreeView* convertTreeView;
	Gtk::Label* convertWindowMessage;
	Glib::RefPtr<Gtk::ListStore> convertTreeModel;
	Glib::RefPtr<Gtk::TreeView::Selection> convertSelection;
	bool converting;
};

} /* namespace Gui */
#endif /* CONVERTWINDOW_H_ */
