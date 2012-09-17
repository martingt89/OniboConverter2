/* ---------------------------------------------------------------------------
** Author: Martin Geier
** overwritedialog.cpp is part of OniboConverter2.
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
	filePath->set_text(file->getMediaConvert()->getOutputFilePath().getPath());
	std::string name = file->getMediaConvert()->getOutputFilePath().getLastPathPart();
	std::string containerSuffix = "."+file->getMediaConvert()->getContainerName();

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
		actualFile->getMediaConvert()->setNewName(newName->get_text());
	}
	actualFile = NULL;
	getNext();
}
void OverwriteDialog::overwriteClicked(){
	if(actualFile != NULL){
		actualFile->getMediaConvert()->enableOverwriteFile();
	}
	actualFile = NULL;
	getNext();
}
void OverwriteDialog::cancelClicked(){
	if(actualFile != NULL){
		actualFile->getMediaConvert()->abort();
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
