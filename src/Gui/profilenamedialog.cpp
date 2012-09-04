/*
 * profilenamedialog.cpp
 *
 *  Created on: 24.8.2012
 *      Author: martint
 */

#include "profilenamedialog.h"
#include <gtkmm/stock.h>

namespace Gui {

ProfileNameDialog::ProfileNameDialog(const Glib::RefPtr<Gtk::Builder>& refGlade) {
	refGlade->get_widget("profileNameDialog", profileNameDialog);
	refGlade->get_widget("profileNameEntry", profileNameEntry);
	refGlade->get_widget("profileNameMessage", profileNameMessage);

	profileNameDialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	profileNameDialog->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

}

ProfileNameDialog::~ProfileNameDialog() {}

bool ProfileNameDialog::getName(std::string& name){
	profileNameEntry->set_text("");
	profileNameMessage->set_text("");
	while(profileNameDialog->run() == Gtk::RESPONSE_OK){
		if(profileNameEntry->get_text().size() == 0){
			profileNameMessage->set_markup(std::string("<span color='red'>")+
					"Invalid profile name"+std::string("</span>"));
		}else{
			name = profileNameEntry->get_text();
			profileNameDialog->hide();
			return true;
		}
	}
	profileNameDialog->hide();
	return false;
}

} /* namespace Gui */
