/*
 * convertwindow.cpp
 *
 *  Created on: 21.8.2012
 *      Author: martint
 */

#include "convertwindow.h"
#include <gtkmm/cellrendererprogress.h>
#include <gtkmm/stock.h>
namespace Gui {

ConvertWindow::ConvertWindow(const Glib::RefPtr<Gtk::Builder>& refGlade) {
	converting = false;
	abort = false;

	loadWidgets(refGlade);
	initConvertTreeView();
	initStopDialog();

	closeConvertButton->signal_clicked().connect(sigc::mem_fun(*this, &ConvertWindow::closePage));
	stopConvertButton->signal_clicked().connect(sigc::mem_fun(*this, &ConvertWindow::stopConvertingSignal));
}

ConvertWindow::~ConvertWindow() {
	delete closeConvertButton;
	delete stopConvertButton;
	delete workingIndicator;
	delete convertTreeView;
	delete convertWindowMessage;
}

void ConvertWindow::display(CppExtension::HashMap<int, MediaFile::MediaFile*> files, bool isEnd){
	typedef Gtk::TreeModel::Children type_children;
	type_children children = convertTreeModel->children();
	for(type_children::iterator iter = children.begin(); iter != children.end(); ++iter){
		Gtk::TreeModel::Row row = *iter;
		 MediaFile::MediaFile* file = files.get(row[modelColumns.fileID]);
		 row[modelColumns.time] = file->getRemainingTime();
		 row[modelColumns.percentage] = file->getPercentage();
			row[modelColumns.state] = file->getConvertStateAsString();
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
void ConvertWindow::initConversion(std::list<MediaFile::MediaFile*> files){
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
		row[modelColumns.state] = file->getConvertStateAsString();
	}
}
sigc::signal<void>& ConvertWindow::signalHide(){
	return hideEvent;
}

void ConvertWindow::closePage(){
	hideEvent();
}
void ConvertWindow::loadWidgets(const Glib::RefPtr<Gtk::Builder>& refGlade) {
	refGlade->get_widget("stopConvertButton", stopConvertButton);
	refGlade->get_widget("closeConvertButton", closeConvertButton);
	refGlade->get_widget("workingIndicator", workingIndicator);
	refGlade->get_widget("convertTreeView", convertTreeView);
	refGlade->get_widget("convertWindowMessage", convertWindowMessage);
	refGlade->get_widget("stopConvertingDialog", stopConvertingDialog);
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

void ConvertWindow::initStopDialog() {
	stopConvertingDialog->add_button(Gtk::Stock::NO, Gtk::RESPONSE_CANCEL);
	stopConvertingDialog->add_button(Gtk::Stock::YES, Gtk::RESPONSE_OK);
}
} /* namespace Gui */
