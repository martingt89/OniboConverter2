/* ---------------------------------------------------------------------------
** Author: Martin Geier
** overwritedialog.h is part of OniboConverter2.
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

#ifndef OVERWRITEDIALOG_H_
#define OVERWRITEDIALOG_H_

#include <list>
#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/builder.h>
#include "../MediaFile/mediafile.h"
#include "convertwindow.h"

namespace Gui {

class OverwriteDialog {
public:
	OverwriteDialog(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~OverwriteDialog();
	void addFile(MediaFile::MediaFile*& file);
private:
	void loadWidgets(const Glib::RefPtr<Gtk::Builder>& refGlade);
	void showFile(MediaFile::MediaFile*& file);
	void overwriteClicked();
	void cancelClicked();
	void renameClicked();
	void getNext();
	void hide();

	std::list<MediaFile::MediaFile*> files;
	MediaFile::MediaFile* actualFile;
	Gtk::Window* overwriteWindow;
	Gtk::Entry* filePath;
	Gtk::Entry* newName;
	Gtk::Button* overwrite;
	Gtk::Button* rename;
	Gtk::Button* cancel;
	Gtk::Label* suffix;
};

} /* namespace Gui */
#endif /* OVERWRITEDIALOG_H_ */
