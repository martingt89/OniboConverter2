/*
 * overwritedialog.cpp
 *
 *  Created on: 30.8.2012
 *      Author: martint
 */

#include "overwritedialog.h"
#include <algorithm>

namespace Gui {

OverwriteDialog::OverwriteDialog(const Glib::RefPtr<Gtk::Builder>& refGlade) {
	refGlade->get_widget("overwriteWindow", overwriteWindow);
	refGlade->get_widget("overwriteButton", overwrite);
	refGlade->get_widget("overwriteRename", rename);
	refGlade->get_widget("overwriteCancel", cancel);
	refGlade->get_widget("overwriteFilePath",filePath);
	refGlade->get_widget("overwriteNewName",newName);
	refGlade->get_widget("overwriteSuffix",suffix);

	actualFile = NULL;

	rename->signal_clicked().connect(sigc::mem_fun(*this, &OverwriteDialog::renameClicked));
	overwrite->signal_clicked().connect(sigc::mem_fun(*this, &OverwriteDialog::overwriteClicked));
	cancel->signal_clicked().connect(sigc::mem_fun(*this, &OverwriteDialog::cancelClicked));
	overwriteWindow->signal_show().connect(sigc::mem_fun(*this, &OverwriteDialog::show));
	overwriteWindow->signal_hide().connect(sigc::mem_fun(*this, &OverwriteDialog::hide));
//	convertWindow = NULL;
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
void OverwriteDialog::setConvertWindow(ConvertWindow* convertWindow){
//	this->convertWindow = convertWindow;
}
void OverwriteDialog::showFile(MediaFile::MediaFile*& file){
	filePath->set_text(file->getPath().getPath());
	newName->set_text(file->getPath().getLastPathPart());
	suffix->set_text("."+file->getContainerName());
}
void OverwriteDialog::show(){
//	convertWindow->set_modal(false);
}
void OverwriteDialog::hide(){
//	convertWindow->set_modal(true);
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
			if(!overwriteWindow->get_visible()){
				overwriteWindow->show();
			}
		}
	}
}
} /* namespace Gui */
