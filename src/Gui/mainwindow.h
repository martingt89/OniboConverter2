/* ---------------------------------------------------------------------------
** Author: Martin Geier
** mainwindow.h is part of OniboConverter2.
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
