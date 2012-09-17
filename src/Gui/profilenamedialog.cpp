/* ---------------------------------------------------------------------------
** Author: Martin Geier
** profilenamedialog.cpp is part of OniboConverter2.
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
			profileNameMessage->set_markup(
					std::string("<span color='red'>") + "Invalid profile name"+std::string("</span>") );
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
