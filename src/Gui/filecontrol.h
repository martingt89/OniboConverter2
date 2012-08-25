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
#include "../CppExtension/path.h"
#include <list>
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
	struct PathWithFileId{
		Path path;
		int id;
	};
public:
	FileControl(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~FileControl();
	std::list<PathWithFileId> getAllFiles() const;
	bool getSelectedFile(PathWithFileId& file) const;
	sigc::signal<void, PathWithFileId>& signalInfo();
	sigc::signal<void, PathWithFileId>& signalDelete();
private:
	void addFileClicked();
	void removeFileClicked();
	void clearFileClicked();
	void fileInfoButtonClicked();
	void fileTreeViewActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
	void onFileDrop(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
	          const Gtk::SelectionData& selection_data, guint info, guint time);
	void addFileEntry(const std::string& file);
	bool onKeyRelease(GdkEventKey* event);
	Gtk::TreeView* fileTreeView;
	Glib::RefPtr<Gtk::ListStore> fileTreeModel;
	Glib::RefPtr<Gtk::TreeView::Selection> fileSelection;
	Gtk::FileChooserDialog fileChooser;
	Gtk::Button* addFile;
	Gtk::Button* removeFile;
	Gtk::Button* clearFiles;
	Gtk::Button* fileInfoButton;
	int fileCounter;
	sigc::signal<void, PathWithFileId> infoEvent;
	sigc::signal<void, PathWithFileId> deleteEvent;
};

} /* namespace Gui */
#endif /* FILECONTROL_H_ */
