/* ---------------------------------------------------------------------------
** Author: Martin Geier
** usersettingsdialog.h is part of OniboConverter2.
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

#ifndef USERSETTINGSDIALOG_H_
#define USERSETTINGSDIALOG_H_

#include <list>
#include <gtkmm/builder.h>
#include <gtkmm/dialog.h>
#include "subsettings.h"

namespace Gui {
namespace Settings {

class UserSettingsDialog {
public:
	UserSettingsDialog(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~UserSettingsDialog();
	void start();
private:
	void aktualizeGlobalSettings();
	void initGraphicElements();
	Gtk::Dialog* userSettingsDialog;
	std::list<SubSetting*> subSettings;
};

} /* namespace Settings */
} /* namespace Gui */
#endif /* USERSETTINGSDIALOG_H_ */
