/*
 * encodersdialog.cpp
 *
 *  Created on: 7.7.2012
 *      Author: martint
 */

#include "encodersdialog.h"

#include <gtkmm/stock.h>

namespace GUI {

EncodersDialog::EncodersDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade):
	Gtk::Dialog(cobject){

	refGlade->get_widget("selector",selector);

	this->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	this->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

}

bool EncodersDialog::start(const std::list<std::pair<std::string, std::string> >& list, std::string &encoder){

	if(list.size() == 0) return false;
	selector->remove_all();

	std::list<std::pair<std::string, std::string> >::const_iterator it;
	std::string table[list.size()];
	int i = 0;
	for(it = list.begin(); it != list.end(); ++it){
		table[i++] = it->first;
		selector->append(it->first +" ==> "+it->second);
	}
	selector->set_active(0);
	int ret = this->run();
	this->hide();

	if(ret == Gtk::RESPONSE_OK){
		int row = selector->get_active_row_number();
		if(row >= 0){
			encoder = table[row];
			return true;
		}
	}
	return false;
}

EncodersDialog::~EncodersDialog() {
	// TODO Auto-generated destructor stub
}

}
