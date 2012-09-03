/*
 * overwritedialog.cpp
 *
 *  Created on: 30.8.2012
 *      Author: martint
 */

#include "overwritedialog.h"
#include <algorithm>

namespace Gui {

OverwriteDialog::OverwriteDialog(const Glib::RefPtr<Gtk::Builder>& refGlade) : actualFile(NULL) {
	loadWidgets(refGlade);

	rename->signal_clicked().connect(sigc::mem_fun(*this, &OverwriteDialog::renameClicked));
	overwrite->signal_clicked().connect(sigc::mem_fun(*this, &OverwriteDialog::overwriteClicked));
	cancel->signal_clicked().connect(sigc::mem_fun(*this, &OverwriteDialog::cancelClicked));
	overwriteWindow->signal_hide().connect(sigc::mem_fun(*this, &OverwriteDialog::hide));
}

OverwriteDialog::~OverwriteDialog() {}

void OverwriteDialog::addFile(MediaFile::MediaFile*& file){
	if(files.size() == 0 && actualFile == NULL){
		actualFile = file;
		showFile(actualFile);
		overwriteWindow->show();
	}else{
		if(actualFile != file){
			auto iter = std::find_if(files.begin(), files.end(),
					[file](const MediaFile::MediaFile* sec) -> bool {
				return file == sec;
			});
			if(iter == files.end()){
				files.push_back(file);
			}
		}
	}
}
void OverwriteDialog::showFile(MediaFile::MediaFile*& file){
	filePath->set_text(file->getOutputFilePath().getPath());
	std::string name = file->getOutputFilePath().getLastPathPart();
	std::string containerSuffix = "."+file->getContainerName();

	if(name.substr(name.size()-containerSuffix.size()) == containerSuffix){
		name = name.substr(0, name.size() - containerSuffix.size());
	}
	newName->set_text(name);
	suffix->set_text(containerSuffix);
}
void OverwriteDialog::hide(){
	cancelClicked();
}
void OverwriteDialog::renameClicked(){
	if(actualFile != NULL){
		actualFile->setName(newName->get_text());
	}
	actualFile = NULL;
	getNext();
}
void OverwriteDialog::overwriteClicked(){
	if(actualFile != NULL){
		actualFile->enableOverwriteFile();
	}
	actualFile = NULL;
	getNext();
}
void OverwriteDialog::cancelClicked(){
	if(actualFile != NULL){
		actualFile->abort();
	}
	actualFile = NULL;
	getNext();
}
void OverwriteDialog::getNext(){
	if(files.size() == 0 && overwriteWindow->get_visible()){
		overwriteWindow->hide();
	}else{
		if(files.size() > 0){
			actualFile = files.front();
			files.pop_front();
			showFile(actualFile);
			if(!overwriteWindow->get_visible()){
				overwriteWindow->show();
			}
		}
	}
}
void OverwriteDialog::loadWidgets(const Glib::RefPtr<Gtk::Builder>& refGlade) {
	refGlade->get_widget("overwriteWindow", overwriteWindow);
	refGlade->get_widget("overwriteButton", overwrite);
	refGlade->get_widget("overwriteRename", rename);
	refGlade->get_widget("overwriteCancel", cancel);
	refGlade->get_widget("overwriteFilePath", filePath);
	refGlade->get_widget("overwriteNewName", newName);
	refGlade->get_widget("overwriteSuffix", suffix);
}
} /* namespace Gui */
