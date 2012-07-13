/*
 * containercombobox.h
 *
 *  Created on: 5.7.2012
 *      Author: martint
 */

#ifndef CONTAINERCOMBOBOX_H_
#define CONTAINERCOMBOBOX_H_

#include <gtkmm/comboboxtext.h>
#include <gtkmm/builder.h>
#include "videosettings.h"
//#include "audiosettings.h" //todo implement
#include "../datakeeper.h"

namespace GUI {

class ContainerComboBox : public Gtk::ComboBoxText{
public:
	ContainerComboBox(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	void setData(DataKeeper& keeper);
	sigc::signal<void> userEvent;
protected:
	virtual void on_changed ();
private:
	const Glib::RefPtr<Gtk::Builder>& refGlade;
	VideoSettings videoSettings;
};

} /* namespace GUI */
#endif /* CONTAINERCOMBOBOX_H_ */
