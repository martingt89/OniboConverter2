/*
 * onibowindow.cpp
 *
 *  Created on: 5.7.2012
 *      Author: martint
 */

#include "onibowindow.h"
#include "gtkmm/main.h"

namespace GUI {

OniboWindow::OniboWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) :
		Gtk::Window(cobject), refGlade(refGlade){

	refGlade->get_widget_derived("a_v_settings", settings);

	startConvert = 0;
	addFile = 0;
	removeFile = 0;
	clear = 0;

	memoryManager.addObject(settings);
	memoryManager.addObject(startConvert);
	memoryManager.addObject(addFile);
	memoryManager.addObject(removeFile);
	memoryManager.addObject(clear);
}
void OniboWindow::setData(DataKeeper& keeper){
	settings->setData(keeper);
}

} /* namespace GUI */
