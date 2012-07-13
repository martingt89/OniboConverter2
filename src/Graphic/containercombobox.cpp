/*
 * containercombobox.cpp
 *
 *  Created on: 5.7.2012
 *      Author: martint
 */

#include "containercombobox.h"

namespace GUI {

ContainerComboBox::ContainerComboBox(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
	: Gtk::ComboBoxText(cobject), refGlade(refGlade), videoSettings(refGlade, userEvent){

}

void ContainerComboBox::on_changed(){
	videoSettings.setActualContainer(this->get_active_text());
	userEvent();
}

void ContainerComboBox::setData(DataKeeper& keeper){
	videoSettings.setData(keeper);
	std::list<std::string> containers = keeper.getAVBox()->getContainerList();
	std::list<std::string>::iterator it;
	for(it = containers.begin(); it != containers.end(); ++it){
		this->append(*it);
	}
}

} /* namespace GUI */
