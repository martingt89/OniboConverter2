/*
 * profilenamedialog.h
 *
 *  Created on: 24.8.2012
 *      Author: martint
 */

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
