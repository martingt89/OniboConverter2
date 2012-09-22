/* ---------------------------------------------------------------------------
** Author: Martin Geier
** importexport.h is part of OniboConverter2.
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

#ifndef IMPORTEXPORT_H_
#define IMPORTEXPORT_H_

#include <gtkmm/builder.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/filechooserdialog.h>
#include "avcontrol.h"
#include "../Profile/profiles.h"

namespace Gui {

class ImportExport {
public:
	ImportExport(const Glib::RefPtr<Gtk::Builder>& refGlade, MediaElement::ElementsDB& elementsDB);
	virtual ~ImportExport();
	void setAVControl(AVControl* avcontrol);
	void setProfiles(Profile::Profiles* profiles);
private:
	void importProfileClicked();
	void exportProfileClicked();
	MediaElement::ElementsDB& elementsDB;
	Gtk::MenuItem *importProfile;
	Gtk::MenuItem *exportProfile;
	Gtk::FileChooserDialog fileSaveDialog;
	Gtk::FileChooserDialog fileLoadDialog;
	AVControl* avcontrol;
	Profile::Profiles* profiles;
};

} /* namespace Gui */
#endif /* IMPORTEXPORT_H_ */
