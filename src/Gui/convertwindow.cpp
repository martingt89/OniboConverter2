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

ConvertWindow::ConvertWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) :
		Gtk::Window(cobject) {
	converting = false;
	abort = false;

	loadWidgets(refGlade);
	initConvertTreeView();
	initStopDialog();

	closeConvertButton->signal_clicked().connect(sigc::mem_fun(*this, &ConvertWindow::hide));
	okConvertButton->signal_clicked().connect(sigc::mem_fun(*this, &ConvertWindow::hide));
}

ConvertWindow::~ConvertWindow() {
	delete convertWindow;
	delete closeConvertButton;
	delete okConvertButton;
	delete workingIndicator;
	delete convertTreeView;
	delete convertWindowMessage;
}

void ConvertWindow::display(CppExtension::HashMap<int, MediaFile::MediaFile*> files, bool isEnd){
	if (!convertWindow->get_visible()) {
		converting = true;
		abort = false;
		convertWindowMessage->set_text("");
		convertTreeModel->clear();
		closeConvertButton->set_visible(true);
		okConvertButton->set_visible(false);
		workingIndicator->set_visible(true);
		workingIndicator->start();
		convertWindow->set_visible(true);
		for (auto file : files.getListOfValues()) {
			Gtk::TreeModel::Row row = *(convertTreeModel->append());
			row[modelColumns.fileID] = file->getFileId();
			row[modelColumns.name] = file->getShortName();
			row[modelColumns.time] = file->getRemainingTime();
			row[modelColumns.percentage] = file->getPercentage();
			row[modelColumns.state] = file->getConvertState();
		}
	}else{
		typedef Gtk::TreeModel::Children type_children;
		type_children children = convertTreeModel->children();
		for(type_children::iterator iter = children.begin(); iter != children.end(); ++iter){
			Gtk::TreeModel::Row row = *iter;
			 MediaFile::MediaFile* file = files.get(row[modelColumns.fileID]);
			 row[modelColumns.time] = file->getRemainingTime();
			 row[modelColumns.percentage] = file->getPercentage();
			 	row[modelColumns.state] = file->getConvertState();
		}
	}
	if(isEnd){
		workingIndicator->stop();
		workingIndicator->set_visible(false);
		closeConvertButton->set_visible(false);
		okConvertButton->set_visible(true);
		convertWindowMessage->set_text("Converting done");
		converting = false;
	}
}
bool ConvertWindow::isAbort(){
	return abort;
}
void ConvertWindow::on_hide (){		//overload
	if(converting){
		int res = stopConvertingDialog->run();
		stopConvertingDialog->hide();
		if(res == Gtk::RESPONSE_OK){
			abort = true;
		}
	}else{
		Gtk::Window::on_hide();
	}
}
void ConvertWindow::loadWidgets(const Glib::RefPtr<Gtk::Builder>& refGlade) {
	refGlade->get_widget("convertWindow", convertWindow);
	refGlade->get_widget("closeConvertButton", closeConvertButton);
	refGlade->get_widget("okConvertButton", okConvertButton);
	refGlade->get_widget("workingIndicator", workingIndicator);
	refGlade->get_widget("convertTreeView", convertTreeView);
	refGlade->get_widget("convertWindowMessage", convertWindowMessage);
	refGlade->get_widget("stopConvertingDialog", stopConvertingDialog);
}

void ConvertWindow::initConvertTreeView() {
	convertTreeModel = Gtk::ListStore::create(modelColumns);
	convertTreeView->set_model(convertTreeModel);
	convertSelection = convertTreeView->get_selection();
	convertTreeView->append_column("Id", modelColumns.fileID);
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
