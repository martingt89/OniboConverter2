/* ---------------------------------------------------------------------------
** Author: Martin Geier
** convertwindow.cpp is part of OniboConverter2.
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

#include "convertwindow.h"
#include <gtkmm/cellrendererprogress.h>
#include <gtkmm/stock.h>
#include "../ProcessExecutor/process.h"

namespace Gui {

ConvertWindow::ConvertWindow(const Glib::RefPtr<Gtk::Builder>& refGlade) {
	converting = false;
	abort = false;

	loadWidgets(refGlade);
	initConvertTreeView();
	initStopDialog();
	initOutputDialog();

	closeConvertButton->signal_clicked().connect(sigc::mem_fun(*this, &ConvertWindow::closePage));
	stopConvertButton->signal_clicked().connect(sigc::mem_fun(*this, &ConvertWindow::stopConvertingSignal));
	infoConvertButton->signal_clicked().connect(sigc::mem_fun(*this, &ConvertWindow::infoConvertSignal));
	convertTreeView->signal_row_activated().connect(sigc::mem_fun(*this, &ConvertWindow::fileTreeViewActivated));
	showDestinationButton->signal_clicked().connect(sigc::mem_fun(*this, &ConvertWindow::showDestination));
}

ConvertWindow::~ConvertWindow() {
	delete closeConvertButton;
	delete stopConvertButton;
	delete workingIndicator;
	delete convertTreeView;
	delete convertWindowMessage;
}

void ConvertWindow::display(bool isEnd){
	typedef Gtk::TreeModel::Children type_children;
	type_children children = convertTreeModel->children();
	for(type_children::iterator iter = children.begin(); iter != children.end(); ++iter){
		Gtk::TreeModel::Row row = *iter;
		 MediaFile::MediaFile* file = idToMediaFile.get(row[modelColumns.fileID]);
		 row[modelColumns.time] = file->getMediaConvert()->getRemainingTime();
		 row[modelColumns.percentage] = file->getMediaConvert()->getPercentage();
			row[modelColumns.state] = file->getMediaConvert()->getConvertStateAsString();
	}
	if(isEnd){
		workingIndicator->stop();
		workingIndicator->set_visible(false);
		closeConvertButton->set_visible(true);
		stopConvertButton->set_visible(false);
		convertWindowMessage->set_text("Converting done");
		converting = false;
	}
}
bool ConvertWindow::isAbort(){
	return abort;
}
void ConvertWindow::stopConvertingSignal(){
	if(converting){
		int res = stopConvertingDialog->run();
		stopConvertingDialog->hide();
		if(res == Gtk::RESPONSE_OK){
			abort = true;
		}
	}else{
		hideEvent();
	}
}
void ConvertWindow::infoConvertSignal(){
	auto iter = convertSelection->get_selected();
	if(iter){
		Gtk::TreeModel::Row row = *iter;
		int fileId = row[modelColumns.fileID];
		MediaFile::MediaFile* file = idToMediaFile.get(fileId);
		if(file->getMediaConvert()->isEnded()){	//todo remove?
			convertOutputText->get_buffer()->set_text(file->getMediaConvert()->getOutput());
			convertOutputDialog->run();
			convertOutputDialog->hide();
		}
	}
}
void ConvertWindow::fileTreeViewActivated(const Gtk::TreeModel::Path&, Gtk::TreeViewColumn*){
	infoConvertSignal();
}

void ConvertWindow::initConversion(std::list<MediaFile::MediaFile*>& files, const Path& destination){
	this->destination = destination;
	for(auto x : files){
		idToMediaFile.set(x->getFileId(), x);
	}
	converting = true;
	abort = false;
	convertWindowMessage->set_text("");
	convertTreeModel->clear();
	closeConvertButton->set_visible(false);
	stopConvertButton->set_visible(true);
	workingIndicator->set_visible(true);
	workingIndicator->start();
	for (auto file : files) {
		Gtk::TreeModel::Row row = *(convertTreeModel->append());
		row[modelColumns.fileID] = file->getFileId();
		row[modelColumns.name] = file->getShortName();
		row[modelColumns.time] = "N/A";
		row[modelColumns.percentage] = 0;
		row[modelColumns.state] = file->getMediaConvert()->getConvertStateAsString();
	}
}
sigc::signal<void>& ConvertWindow::signalHide(){
	return hideEvent;
}

void ConvertWindow::closePage(){
	hideEvent();
}
void ConvertWindow::showDestination(){
	std::list<std::string> args;
	args.push_back(destination.getPath());
	ProcessExecutor::Process process("xdg-open", args);
	int res = process.waitForProcessEnd();
	if(res != 0){
		//process.getStdOut() >>
	}
	//todo log res
}
void ConvertWindow::loadWidgets(const Glib::RefPtr<Gtk::Builder>& refGlade) {
	refGlade->get_widget("stopConvertButton", stopConvertButton);
	refGlade->get_widget("closeConvertButton", closeConvertButton);
	refGlade->get_widget("infoConvertButton", infoConvertButton);
	refGlade->get_widget("openDestinationPath", showDestinationButton);
	refGlade->get_widget("workingIndicator", workingIndicator);
	refGlade->get_widget("convertTreeView", convertTreeView);
	refGlade->get_widget("convertWindowMessage", convertWindowMessage);
	refGlade->get_widget("stopConvertingDialog", stopConvertingDialog);
	refGlade->get_widget("converterOutputDialog", convertOutputDialog);
	refGlade->get_widget("converterOutputText", convertOutputText);
}

void ConvertWindow::initConvertTreeView() {
	convertTreeModel = Gtk::ListStore::create(modelColumns);
	convertTreeView->set_model(convertTreeModel);
	convertSelection = convertTreeView->get_selection();
	convertTreeView->append_column("Name", modelColumns.name);
	convertTreeView->append_column("Remaining time", modelColumns.time);
	convertTreeView->append_column("State", modelColumns.state);
	Gtk::CellRendererProgress* cell = Gtk::manage(new Gtk::CellRendererProgress);
	int cols_count = convertTreeView->append_column("Progress", *cell);
	Gtk::TreeViewColumn* pColumn = convertTreeView->get_column(cols_count - 1);
	if (pColumn) {
		pColumn->add_attribute(cell->property_value(), modelColumns.percentage);
	}
}
void ConvertWindow::initOutputDialog(){
	convertOutputDialog->add_button(Gtk::Stock::CLOSE, Gtk::RESPONSE_CLOSE);
	convertOutputText->set_buffer(Gtk::TextBuffer::create());
}
void ConvertWindow::initStopDialog() {
	stopConvertingDialog->add_button(Gtk::Stock::NO, Gtk::RESPONSE_CANCEL);
	stopConvertingDialog->add_button(Gtk::Stock::YES, Gtk::RESPONSE_OK);
}
} /* namespace Gui */
