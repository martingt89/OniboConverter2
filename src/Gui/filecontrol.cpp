/*
 * filecontrol.cpp
 *
 *  Created on: 17.8.2012
 *      Author: martint
 */

#include "filecontrol.h"
#include <gtkmm/stock.h>
namespace Gui {

//todo add drag & drop
//todo add del key shortcut

FileControl::FileControl(const Glib::RefPtr<Gtk::Builder>& refGlade) :
		fileChooser("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN), fileCounter(0){

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

std::list<FileControl::PathWithFileId> FileControl::getAllFiles() const{
	std::list<FileControl::PathWithFileId> files;
	typedef Gtk::TreeModel::Children type_children;
	type_children children = fileTreeModel->children();
	for (type_children::iterator iter = children.begin(); iter != children.end(); ++iter) {
		Gtk::TreeModel::Row row = *iter;
		FileControl::PathWithFileId file;
		file.path = Path((Glib::ustring)row[modelColumns.path]);
		file.id = row[modelColumns.id];
		files.push_back(file);
	}
	return files;
}

void FileControl::addFileClicked(){
	int res = fileChooser.run();
	fileChooser.hide();
	if(res == Gtk::RESPONSE_OK){
		std::vector< std::string > files = fileChooser.get_filenames ();
		for(std::string file : files){
			Gtk::TreeModel::Row row = *(fileTreeModel->append());
			row[modelColumns.path] = file;
			row[modelColumns.id] = fileCounter;
			fileCounter++;
		}
	}
}
void FileControl::removeFileClicked(){
	Gtk::TreeModel::iterator iter = fileSelection->get_selected();
	if(iter){
		fileTreeModel->erase(iter);
	}
}
void FileControl::clearFileClicked(){
	fileTreeModel->clear();
}
} /* namespace Gui */
