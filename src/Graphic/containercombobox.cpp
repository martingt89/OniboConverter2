/*
 * containercombobox.cpp
 *
 *  Created on: 5.7.2012
 *      Author: martint
 */

#include "containercombobox.h"
#include <iostream> //todo remove

namespace GUI {

ContainerComboBox::ContainerComboBox(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
	: Gtk::ComboBoxText(cobject), refGlade(refGlade), videoSettings(refGlade){

	this->suportedEncoders = NULL;
	this->audioVideoData = NULL;
	this->guiData = NULL;
	this->convert = NULL;

}

ContainerComboBox::~ContainerComboBox() {
	// TODO Auto-generated destructor stub
}

void ContainerComboBox::on_changed (){
	if(/*manualna zmena*/1){
		changeContent();
	}
}

void ContainerComboBox::changeContent(){
	videoSettings.setActualContainer(this->get_active_text());
}

void ContainerComboBox::setNeedsData(AVBox::SupportedEncoders *suportedEncoders,
					AVBox::AVBox *audioVideoData,
					AVBox::GuiSettings *guiData,
					AVBox::FormatToEncoders *convert){
	this->suportedEncoders = suportedEncoders;
	this->audioVideoData = audioVideoData;
	this->guiData = guiData;
	this->convert = convert;


	std::list<std::string> containers = audioVideoData->getContainerList();
	std::list<std::string>::iterator it;
	for(it = containers.begin(); it != containers.end(); ++it){
		this->append(*it);
	}

	videoSettings.setNeedsData(suportedEncoders, audioVideoData, guiData, convert);
}

} /* namespace GUI */
