/* ---------------------------------------------------------------------------
** Author: Martin Geier
** profilenamedialog.h is part of OniboConverter2.
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

#ifndef PROFILENAMEDIALOG_H_
#define PROFILENAMEDIALOG_H_

#include <gtkmm/builder.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>

namespace Gui {

class ProfileNameDialog {
public:
	ProfileNameDialog(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~ProfileNameDialog();
	bool getName(std::string& name);
private:
	Gtk::Dialog* profileNameDialog;
	Gtk::Entry* profileNameEntry;
	Gtk::Label* profileNameMessage;
};

} /* namespace Gui */
#endif /* PROFILENAMEDIALOG_H_ */
