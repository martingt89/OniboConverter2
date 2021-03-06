/* ---------------------------------------------------------------------------
** Author: Martin Geier
** filecontrol.cpp is part of OniboConverter2.
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

#include "filecontrol.h"
#include <gtkmm/stock.h>
#include <glibmm/convert.h>

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
	refGlade->get_widget("fileInfoButton", fileInfoButton);

	refGlade->get_widget("addFileMenuItem", addFileMenuItem);
	refGlade->get_widget("removeFileMenuItem", removeFileMenuItem);
	refGlade->get_widget("clearFilesMenuItem", clearFilesMenuItem);
	refGlade->get_widget("fileInfoButtonMenuItem", fileInfoButtonMenuItem);

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
	fileInfoButton->signal_clicked().connect(sigc::mem_fun(*this, &FileControl::fileInfoButtonClicked));
	addFileMenuItem->signal_activate().connect(sigc::mem_fun(*this, &FileControl::addFileClicked));
	removeFileMenuItem->signal_activate().connect(sigc::mem_fun(*this, &FileControl::removeFileClicked));
	clearFilesMenuItem->signal_activate().connect(sigc::mem_fun(*this, &FileControl::clearFileClicked));
	fileInfoButtonMenuItem->signal_activate().connect(sigc::mem_fun(*this, &FileControl::fileInfoButtonClicked));
	fileTreeView->signal_row_activated().connect(sigc::mem_fun(*this, &FileControl::fileTreeViewActivated));
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
sigc::signal<void, FileControl::PathWithFileId>& FileControl::signalInfo(){
	return infoEvent;
}
sigc::signal<void, FileControl::PathWithFileId> &FileControl::signalDelete(){
	return deleteEvent;
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
		Gui::FileControl::PathWithFileId file;
		if(getSelectedFile(file)){
			deleteEvent(file);
			fileTreeModel->erase(iter);
		}
	}
}
void FileControl::clearFileClicked() {
	typedef Gtk::TreeModel::Children type_children;
	type_children children = fileTreeModel->children();
	for (type_children::iterator iter = children.begin(); iter != children.end(); ++iter) {
		Gtk::TreeModel::Row row = *iter;
		FileControl::PathWithFileId file;
		file.path = Path((Glib::ustring) row[modelColumns.path]);
		file.id = row[modelColumns.id];
		deleteEvent(file);
	}
	fileTreeModel->clear();
}
void FileControl::fileInfoButtonClicked(){
	Gui::FileControl::PathWithFileId file;
	if(getSelectedFile(file)){
		infoEvent(file);
	}
}
void FileControl::fileTreeViewActivated(const Gtk::TreeModel::Path&, Gtk::TreeViewColumn*){
	Gui::FileControl::PathWithFileId file;
	if(getSelectedFile(file)){
		infoEvent(file);
	}
}
void FileControl::onFileDrop(const Glib::RefPtr<Gdk::DragContext>& context, int, int,
		const Gtk::SelectionData& selection_data, guint, guint time) {
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
