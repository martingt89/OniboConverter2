/*
 * mainwindow.h
 *
 *  Created on: 31.8.2012
 *      Author: martint
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <sigc++/sigc++.h>
namespace Gui {

class MainWindow  : public Gtk::Window {
public:
	MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~MainWindow();
	void exit();
	sigc::signal<void>& signalClose();
protected:
	virtual void on_hide ();
private:
	sigc::signal<void> closeEvent;
};

} /* namespace Gui */
#endif /* MAINWINDOW_H_ */
