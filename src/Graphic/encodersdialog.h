/*
 * encodersdialog.h
 *
 *  Created on: 7.7.2012
 *      Author: martint
 */

#ifndef ENCODERSDIALOG_H_
#define ENCODERSDIALOG_H_

#include <gtkmm/builder.h>
#include <gtkmm/dialog.h>
#include <gtkmm/comboboxtext.h>
#include <string>
#include <list>

namespace GUI {

class EncodersDialog : public Gtk::Dialog{
public:
	EncodersDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~EncodersDialog();
	bool start(const std::list<std::pair<std::string, std::string> >& list, std::string &encoder);
private:
	Gtk::ComboBoxText *selector;	//TODO Change to tree view
};

}
#endif /* ENCODERSDIALOG_H_ */
