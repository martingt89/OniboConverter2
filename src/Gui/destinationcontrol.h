/* ---------------------------------------------------------------------------
** Author: Martin Geier
** destinationcontrol.h is part of OniboConverter2.
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

#ifndef DESTINATIONCONTROL_H_
#define DESTINATIONCONTROL_H_

#include <gtkmm/builder.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/filechooserdialog.h>
#include "../CppExtension/path.h"

namespace Gui {

class DestinationControl {
public:
	DestinationControl(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~DestinationControl();
	Path getDestinationPath() const;
private:
	void searchForFolderClicked();
	Gtk::Entry* outputFolder;
	Gtk::Button* searchForFolder;
	Gtk::MenuItem* outputDestMenu;
	Gtk::FileChooserDialog folderChooser;
};

} /* namespace Gui */
#endif /* DESTINATIONCONTROL_H_ */
