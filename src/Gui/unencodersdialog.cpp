/*
 * unencodersdialog.cpp
 *
 *  Created on: 11.9.2012
 *      Author: martin
 */

#include "unencodersdialog.h"

#include <gtkmm/stock.h>
#include "../userpreferences.h"
#include "../helper.h"

namespace Gui {

UnEncodersDialog::UnEncodersDialog(const Glib::RefPtr<Gtk::Builder>& refGlade, MediaElement::ElementsDB& elementsDB) :
		elementsDB(elementsDB){
	refGlade->get_widget("unEncodersDialog", unEncodersDialog);
	refGlade->get_widget("unEncodersText", unEncodersText);
	refGlade->get_widget("unEncoderCheck", unEncodersCheck);
	refGlade->get_widget("showUnEncMenuItem", showUnEncMenuItem);

	changed = false;
	unEncodersDialog->add_button(Gtk::Stock::OK, 0);
	Gdk::RGBA green;
	green.set_rgba(0, 0.5, 0, 1);
	Gdk::RGBA orange;
	orange.set_rgba(1, 0.4, 0, 1);
	Gdk::RGBA red;
	red.set_rgba(0.5, 0, 0, 1);

	greenTag = Gtk::TextBuffer::Tag::create();
	greenTag->property_foreground_rgba() = green;
	greenTag->set_property("size-points", 12);
	orangeTag = Gtk::TextBuffer::Tag::create();
	orangeTag->property_foreground_rgba() = orange;
	orangeTag->set_property("size-points", 12);
	redTag = Gtk::TextBuffer::Tag::create();
	redTag->property_foreground_rgba() = red;
	redTag->set_property("size-points", 12);
	tagTable = Gtk::TextBuffer::TagTable::create();
	tagTable->add(greenTag);
	tagTable->add(orangeTag);
	tagTable->add(redTag);

	unEncodersText->set_buffer(Gtk::TextBuffer::create(tagTable));

	unEncodersCheck->signal_clicked().connect(sigc::mem_fun(*this, &UnEncodersDialog::checkClicked));
	showUnEncMenuItem->signal_activate().connect(sigc::mem_fun(*this, &UnEncodersDialog::show));
}

void UnEncodersDialog::show(){
	auto encoders = elementsDB.getUnsuprtedEncoders();
	unEncodersCheck->set_active(UserPreferences::getInstance()->isDisableShowUnEncoders());
	changed = false;
	auto unsuported = encoders.getEncoders();

	for(auto pair : unsuported){
		Glib::RefPtr<Gtk::TextBuffer::Mark> mark = unEncodersText->get_buffer()->get_insert();
		Glib::RefPtr<Gtk::TextBuffer::Tag> colorTag;
		if(pair.second == Converter::UnsupportedEncoders::MEDIUM){
			colorTag = orangeTag;
		}else{
			colorTag = redTag;
		}


		unEncodersText->get_buffer()->insert_with_tag (mark->get_iter(), toS("⚫ ")+pair.first+"\n", colorTag);
	}

	unEncodersDialog->run();
	unEncodersDialog->hide();

	if(changed){
		UserPreferences::getInstance()->setDisableShowUnEncoders(unEncodersCheck->get_active());
		UserPreferences::getInstance()->save();
	}
}

void UnEncodersDialog::checkClicked(){
	changed = true;
}

} /* namespace Gui */
