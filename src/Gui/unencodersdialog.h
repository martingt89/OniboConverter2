/* ---------------------------------------------------------------------------
** Author: Martin Geier
** unencodersdialog.h is part of OniboConverter2.
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

#ifndef UNENCODERSDIALOG_H_
#define UNENCODERSDIALOG_H_

#include <gtkmm/builder.h>
#include <gtkmm/dialog.h>
#include <gtkmm/textview.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/textbuffer.h>
#include "../Converter/unsupportedencoders.h"
#include "../MediaElement/elementsdb.h"

namespace Gui {

class UnEncodersDialog {
public:
	UnEncodersDialog(const Glib::RefPtr<Gtk::Builder>& refGlade, MediaElement::ElementsDB& elementsDB);
	void show();
private:
	void checkClicked();
	Gtk::Dialog* unEncodersDialog;
	Gtk::TextView* unEncodersText;
	Gtk::CheckButton* unEncodersCheck;
	Gtk::MenuItem* showUnEncMenuItem;
	Glib::RefPtr<Gtk::TextBuffer::Tag> greenTag;
	Glib::RefPtr<Gtk::TextBuffer::Tag> orangeTag;
	Glib::RefPtr<Gtk::TextBuffer::Tag> redTag;
	Glib::RefPtr<Gtk::TextBuffer::TagTable> tagTable;
	MediaElement::ElementsDB& elementsDB;
	bool changed;
};

} /* namespace Gui */
#endif /* UNENCODERSDIALOG_H_ */
