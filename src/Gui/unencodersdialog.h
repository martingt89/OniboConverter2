/*
 * unencodersdialog.h
 *
 *  Created on: 11.9.2012
 *      Author: martin
 */

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
