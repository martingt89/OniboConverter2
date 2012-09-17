/* ---------------------------------------------------------------------------
** Author: Martin Geier
** threading.h is part of OniboConverter2.
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

#ifndef THREADING_H_
#define THREADING_H_

#include "subsettings.h"
#include <gtkmm/builder.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/checkbutton.h>
#include <list>

namespace Gui {
namespace Settings {

class Threading : public SubSetting{
public:
	Threading(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~Threading();
	virtual void initGraphicElements(UserPreferences* preferences);
	virtual void aktualizeGlobalSettings(UserPreferences* preferences);
private:
	void autoNumberOfThreadsClicked();
	Gtk::SpinButton* numberOfThreads;
	Gtk::CheckButton* autoNumberOfThreads;
	Gtk::CheckButton* enableMultForEncoders;
};

} /* namespace Settings */
} /* namespace Gui */
#endif /* THREADING_H_ */
