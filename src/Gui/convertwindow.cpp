/*
 * convertwindow.cpp
 *
 *  Created on: 21.8.2012
 *      Author: martint
 */

#include "convertwindow.h"
#include <gtkmm/cellrendererprogress.h>

namespace Gui {

ConvertWindow::ConvertWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) :
		Gtk::Window(cobject) {
	refGlade->get_widget("convertWindow",convertWindow);
	refGlade->get_widget("closeConvertButton",closeConvertButton);
	refGlade->get_widget("okConvertButton",okConvertButton);
	refGlade->get_widget("workingIndicator",workingIndicator);
	refGlade->get_widget("convertTreeView",convertTreeView);
	refGlade->get_widget("convertWindowMessage",convertWindowMessage);
	converting = false;

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

void ConvertWindow::on_hide (){
	if(converting){
		//std::cout<<"dialog"<<std::endl;	//todo add dialog
											//call back
	}else{
		Gtk::Window::on_hide();
	}
}

} /* namespace Gui */
