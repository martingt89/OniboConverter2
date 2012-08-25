/*
 * filecontrol.cpp
 *
 *  Created on: 17.8.2012
 *      Author: martint
 */

#include "filecontrol.h"
#include <gtkmm/stock.h>

namespace Gui {

FileControl::FileControl(const Glib::RefPtr<Gtk::Builder>& refGlade) :
		fileChooser("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN), fileCounter(0) {

	fileChooser.set_select_multiple(true);
	fileChooser.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	fileChooser.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

	refGlade->get_widget("fileTreeView", fileTreeView);
	refGlade->get_widget("addFile", addFile);
	refGlade->get_widget("removeFile", removeFile);
	refGlade->get_widget("clearFiles", clearFiles);

	fileTreeModel = Gtk::ListStore::create(modelColumns);
	fileTreeView->set_model(fileTreeModel);
	fileSelection = fileTreeView->get_selection();
	fileTreeView->append_column("File path", modelColumns.path);

	std::vector<Gtk::TargetEntry> listTargets;
	listTargets.push_back(Gtk::TargetEntry("text/uri-list"));
	fileTreeView->drag_dest_set(listTargets);
	fileTreeView->signal_drag_data_received().connect(sigc::mem_fun(*this, &FileControl::onFileDrop));

	fileTreeView->add_events(Gdk::KEY_RELEASE_MASK);
	fileTreeView->signal_key_release_event().connect(sigc::mem_fun(*this, &FileControl::onKeyRelease));
	addFile->signal_clicked().connect(sigc::mem_fun(*this, &FileControl::addFileClicked));
	removeFile->signal_clicked().connect(sigc::mem_fun(*this, &FileControl::removeFileClicked));
	clearFiles->signal_clicked().connect(sigc::mem_fun(*this, &FileControl::clearFileClicked));
}

FileControl::~FileControl() {
	delete fileTreeView;
	delete addFile;
	delete removeFile;
	delete clearFiles;
}

std::list<FileControl::PathWithFileId> FileControl::getAllFiles() const {
	std::list<FileControl::PathWithFileId> files;
	typedef Gtk::TreeModel::Children type_children;
	type_children children = fileTreeModel->children();
	for (type_children::iterator iter = children.begin(); iter != children.end(); ++iter) {
		Gtk::TreeModel::Row row = *iter;
		FileControl::PathWithFileId file;
		file.path = Path((Glib::ustring) row[modelColumns.path]);
		file.id = row[modelColumns.id];
		files.push_back(file);
	}
	return files;
}
bool FileControl::getSelectedFile(PathWithFileId& file) const{
	auto iter = fileSelection->get_selected();
	if(iter){
		Gtk::TreeModel::Row row = *iter;
		file.id = (int)row[modelColumns.id];
		file.path = Path((Glib::ustring)row[modelColumns.path]);
		return true;
	}
	return false;
}
void FileControl::addFileClicked() {
	int res = fileChooser.run();
	fileChooser.hide();
	if (res == Gtk::RESPONSE_OK) {
		std::vector<std::string> files = fileChooser.get_filenames();
		for (std::string file : files) {
			addFileEntry(file);
		}
	}
}
void FileControl::removeFileClicked() {
	Gtk::TreeModel::iterator iter = fileSelection->get_selected();
	if (iter) {
		fileTreeModel->erase(iter);
	}
}
void FileControl::clearFileClicked() {
	fileTreeModel->clear();
}
void FileControl::onFileDrop(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
		const Gtk::SelectionData& selection_data, guint info, guint time) {
	const int length = selection_data.get_length();
	if ((length >= 0) && (selection_data.get_format() == 8)) {
		auto uris = selection_data.get_uris();
		for (auto uri : uris) {
			addFileEntry(Glib::filename_from_uri(uri));
		}
	}
	context->drag_finish(false, false, time);
}
void FileControl::addFileEntry(const std::string& file) {
	Gtk::TreeModel::Row row = *(fileTreeModel->append());
	row[modelColumns.path] = file;
	row[modelColumns.id] = fileCounter;
	fileCounter++;
}
bool FileControl::onKeyRelease(GdkEventKey* event) {
	if (event->keyval == GDK_KEY_Delete) {
		removeFileClicked();
	}
	return false;
}
} /* namespace Gui */
