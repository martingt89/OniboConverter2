/*
 * mainwindow.cpp
 *
 *  Created on: 31.8.2012
 *      Author: martint
 */

#include "mainwindow.h"
#include <gtkmm/main.h>

namespace Gui {

MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) :
				Gtk::Window(cobject) {}

MainWindow::~MainWindow() {}

void MainWindow::exit(){
	Gtk::Main::quit();
}
sigc::signal<void>& MainWindow::signalClose(){
	return closeEvent;
}

void MainWindow::on_hide (){
	closeEvent();
}

} /* namespace Gui */
