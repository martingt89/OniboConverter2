/*
 * filecontrol.h
 *
 *  Created on: 17.8.2012
 *      Author: martint
 */

#ifndef FILECONTROL_H_
#define FILECONTROL_H_

#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>


namespace Gui {

class FileControl {
private:
	class ModelColumns: public Gtk::TreeModel::ColumnRecord {
	public:
		ModelColumns() {
			add(path);
			add(id);
		}

		Gtk::TreeModelColumn<Glib::ustring> path;
		Gtk::TreeModelColumn<int> id;
	};
	ModelColumns modelColumns;
public:
	FileControl(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~FileControl();
private:
	void addFileClicked();
	void removeFileClicked();
	void clearFileClicked();
	Gtk::TreeView* fileTreeView;
	Glib::RefPtr<Gtk::ListStore> fileTreeModel;
	Glib::RefPtr<Gtk::TreeView::Selection> fileSelection;
	Gtk::FileChooserDialog fileChooser;
	Gtk::Button* addFile;
	Gtk::Button* removeFile;
	Gtk::Button* clearFiles;
	int fileCounter;
};

} /* namespace Gui */
#endif /* FILECONTROL_H_ */
