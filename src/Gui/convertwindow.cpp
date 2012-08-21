/*
 * convertwindow.cpp
 *
 *  Created on: 21.8.2012
 *      Author: martint
 */

#include "convertwindow.h"
#include <gtkmm/cellrendererprogress.h>
#include <iostream> //todo remove
namespace Gui {

ConvertWindow::ConvertWindow(const Glib::RefPtr<Gtk::Builder>& refGlade) {
	refGlade->get_widget("convertWindow",convertWindow);
	refGlade->get_widget("closeOkConvertButton",closeOkConvertButton);
	refGlade->get_widget("workingIndicator",workingIndicator);
	refGlade->get_widget("convertTreeView",convertTreeView);

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

ConvertWindow::~ConvertWindow() {
	// TODO Auto-generated destructor stub
}

void ConvertWindow::display(CppExtension::HashMap<int, MediaFile::MediaFile*> files){
	if (!convertWindow->get_visible()) {
		convertWindow->set_visible(true);
		convertTreeModel->clear();
		for (auto file : files.getListOfValues()) {
			std::cout<<"file"<<std::endl;
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
}

} /* namespace Gui */
